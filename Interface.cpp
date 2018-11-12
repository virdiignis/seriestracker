//
// Created by prance on 22.10.18.
//

#include "Interface.hpp"

Interface::Interface() {
    initscr();
    keypad(stdscr, true);
    noecho();
    max_y = static_cast<unsigned short>getmaxy(stdscr);
    max_x = static_cast<unsigned short>getmaxx(stdscr);
    if (max_x < MIN_TERM_WIDTH || max_y < MIN_TERM_HEIGHT) throw std::runtime_error("Terminal window too small.");
    if (!has_colors()) throw std::runtime_error("Terminal doesn't support colors.");
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_RED, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_CYAN);
    init_pair(5, COLOR_WHITE, COLOR_BLUE);
    init_pair(6, COLOR_WHITE, COLOR_RED);
    db = Database(series_pool, film_pool, ppv_pool);
    line_s = LineCounter<Series>(&series_pool);
    line_fs = LineCounter<Series *>(&filtered_pool);
    line_f = LineCounter<Film>(&film_pool);
    line_p = LineCounter<Ppv>(&ppv_pool);
}

Interface::~Interface() {
    endwin();
}

void Interface::topKeys() {
    const char *entries[TOP_MENU_ENTRIES_NUM] = TOP_MENU_ENTRIES;
    attron(A_BOLD);
    move(0, 0);
    for (unsigned short i = 0; i < TOP_MENU_ENTRIES_NUM; i++) {
        printw("\t");
        if (view == i + 1) attron(COLOR_PAIR(2));
        else
            attron(COLOR_PAIR(1));
        printw(entries[i]);
        if (view == i + 1) attroff(COLOR_PAIR(2));
        else
            attroff(COLOR_PAIR(1));
    }
    attroff(A_BOLD);

}

void Interface::bottomKeys() {
    std::string *entries = nullptr;
    int *width = nullptr;
    unsigned short entries_num = 0;
    switch (view) {
        case VIEW_SERIES_LIST:
        case VIEW_SERIES_FILTERED:
            entries_num = BOTTOM_MENU_ENTRIES_SERIES_NUM;
            entries = new std::string[entries_num]BOTTOM_MENU_ENTRIES_SERIES;
            width = new int[entries_num]BOTTOM_MENU_ENTRIES_SERIES_WIDTHS;
            break;
        case VIEW_FILMS_LIST:
            entries_num = BOTTOM_MENU_ENTRIES_FILMS_NUM;
            entries = new std::string[entries_num]BOTTOM_MENU_ENTRIES_FILMS;
            width = new int[entries_num]BOTTOM_MENU_ENTRIES_FILMS_WIDTHS;
            break;
        case VIEW_PPVS_LIST:
            entries_num = BOTTOM_MENU_ENTRIES_PPVS_NUM;
            entries = new std::string[entries_num]BOTTOM_MENU_ENTRIES_PPVS;
            width = new int[entries_num]BOTTOM_MENU_ENTRIES_PPVS_WIDTHS;
            break;
        case VIEW_EDIT:
            entries_num = BOTTOM_MENU_ENTRIES_EDIT_NUM;
            entries = new std::string[entries_num]BOTTOM_MENU_ENTRIES_EDIT;
            width = new int[entries_num]BOTTOM_MENU_ENTRIES_EDIT_WIDTHS;
            break;
        default:
            delete[] entries;
            delete[] width;
            return;
    }
    try {
        move(max_y - 1, 0);
        attron(A_BOLD);
        _colorLinePrint(3, entries_num, width, entries);
        attroff(A_BOLD);
    } catch (std::exception &e) {
        delete[] entries;
        delete[] width;
        throw e;
    }
    delete[] entries;
    delete[] width;

}

void Interface::render() {
    switch (view) {
        case VIEW_WELCOME:
            topKeys();
            welcome();
            break;
        case VIEW_SERIES_LIST:
            topKeys();
            list(series_pool, line_s, line_s.getStartLine());
            break;
        case VIEW_FILMS_LIST:
            topKeys();
            list(film_pool, line_f, line_f.getStartLine());
            break;
        case VIEW_PPVS_LIST:
            topKeys();
            list(ppv_pool, line_p, line_p.getStartLine());
            break;
        case VIEW_SERIES_FILTERED:
            topKeys();
            list(filtered_pool, line_fs, line_fs.getStartLine());
            break;
        case VIEW_SERIES:
            details(&(series_pool[line_s]), -1);
            break;
        case VIEW_SERIES_F:
            details(filtered_pool[line_fs], -1);
            break;
        case VIEW_FILM:
            details(&(film_pool[line_f]), -1);
            break;
        case VIEW_PPV:
            details(&(ppv_pool[line_p]), -1);
            break;
        default:
            break;
    }
    bottomKeys();
}

void Interface::welcome() {
    const std::string welcome_string = WELCOME_STRING;
    mvprintw(max_y / 2, (max_x - static_cast<int>(welcome_string.length())) / 2, welcome_string.c_str());
}

void Interface::_list(Pool<Series *> &pool, unsigned int active_line, unsigned int start_line) {
    int columns_width[SERIES_LIST_PARAMS]SERIES_LIST_PARAMS_WIDTHS;
    std::string fields[SERIES_LIST_PARAMS]SERIES_LIST_PARAMS_HEADERS, data[SERIES_LIST_PARAMS];
    move(1, 0);
    _colorLinePrint(2, SERIES_LIST_PARAMS, columns_width, fields);
    unsigned int j;
    std::map<std::string, std::string> m;
    for (int k = start_line; k < start_line + max_y - 3 && k < pool.size() + start_line; ++k) {
        if (k == active_line) attron(COLOR_PAIR(4));
        j = 0;
        m = pool[k]->getListParams();
        for (auto &p: fields) data[j++] = m[p];
        _colorLinePrint(0, SERIES_LIST_PARAMS, columns_width, data);
        if (k == active_line) attroff(COLOR_PAIR(4));
    }
}

template<typename T>
void Interface::_list(Pool<T> &pool, unsigned int active_line, unsigned int start_line) {
    int params = 0, *columns_width = nullptr;
    std::string *fields = nullptr;
    if (typeid(T) == typeid(Series)) {
        params = SERIES_LIST_PARAMS;
        columns_width = new int[SERIES_LIST_PARAMS]SERIES_LIST_PARAMS_WIDTHS;
        fields = new std::string[SERIES_LIST_PARAMS]SERIES_LIST_PARAMS_HEADERS;
    } else if (typeid(T) == typeid(Film)) {
        params = FILM_LIST_PARAMS;
        columns_width = new int[FILM_LIST_PARAMS]FILM_LIST_PARAMS_WIDTHS;
        fields = new std::string[FILM_LIST_PARAMS]FILM_LIST_PARAMS_HEADERS;
    } else if (typeid(T) == typeid(Ppv)) {
        params = PPV_LIST_PARAMS;
        columns_width = new int[PPV_LIST_PARAMS]PPV_LIST_PARAMS_WIDTHS;
        fields = new std::string[PPV_LIST_PARAMS]PPV_LIST_PARAMS_HEADERS;
    } else {
        throw std::runtime_error("Pool of incorrect type passed to list in menu.");
    }

    move(1, 0);
    _colorLinePrint(2, params, columns_width, fields);
    std::string data[params];
    std::map<std::string, std::string> m;
    for (int k = start_line; k < start_line + max_y - 3 && k < pool.size() + start_line; ++k) {
        if (k == active_line) attron(COLOR_PAIR(4));
        m = pool[k].getListParams();
        for (int j = 0; j < params; j++) data[j] = m[fields[j]];
        _colorLinePrint(0, params, columns_width, data);
        if (k == active_line) attroff(COLOR_PAIR(4));
    }

    delete[] columns_width;
    delete[] fields;
}

void Interface::_colorLinePrint(int color_pair, int fields_count, const int *columns_width,
                                const std::string *fields) const {
    attron(COLOR_PAIR(color_pair));
    for (unsigned short int i = 0; i < fields_count; i++) {
        for (int j = 0; j < static_cast<int>(columns_width[i] - fields[i].length()); ++j) printw(" ");
        printw(fields[i].c_str());
    }
    attroff(COLOR_PAIR(color_pair));
}

void Interface::mainLoop() {
    render();
    int key = 0;
    while ((key = getch())) {
        if (view <= VIEW_PPVS_LIST)
            switch (key) {
                case KEY_ARROW_RIGHT:
                    if (view < VIEW_PPVS_LIST) setView(static_cast<unsigned short>(view + 1));
                    break;
                case KEY_ARROW_LEFT:
                    if (view > 1) setView(static_cast<unsigned short>(view - 1));
                    break;
                case KEY_SERIES_LIST:
                    setView(VIEW_SERIES_LIST);
                    break;
                case KEY_FILMS_LIST:
                    setView(VIEW_FILMS_LIST);
                    break;
                case KEY_PPVS_LIST:
                    setView(VIEW_PPVS_LIST);
                    break;
                case KEY_QUIT:
                    return;
                default:
                    break;
            }
        switch (view) {
            case VIEW_WELCOME:
                if (key == KEY_QUIT) return;
                break;
            case VIEW_SERIES_LIST:
                switch (key) {
                    case KEY_ARROW_DOWN:
                        line_s++;
                        setView(view);
                        break;
                    case KEY_ARROW_UP:
                        line_s--;
                        setView(view);
                        break;
                    case KEY_FOLLOW:
                        series_pool[line_s].flipFollow();
                        db.write(series_pool[line_s]);
                        setView(view);
                        break;
                    case KEY_REMOVE:
                    case KEY_DELETE:
                        try {
                            db.remove(series_pool[line_s]);
                            series_pool -= line_s;
                            if (line_s >= series_pool.size()) line_s--;
                        } catch (std::invalid_argument &e) {
                            throw std::invalid_argument("Trying to delete invalid series.");
                        }
                        setView(view);
                        break;
                    case KEY_SORT:
                        series_pool.sort();
                        setView(view);
                        break;
                    case KEY_FILTER:
                        series_filter();
                        break;
                    case KEY_DETAILS:
                    case KEY_ENTER:
                        setView(VIEW_SERIES);
                        break;
                    case KEY_EDIT:
                        edit(series_pool[line_s]);
                        db.write(series_pool[line_s]);
                        setView(VIEW_SERIES_LIST);
                        break;
                    case KEY_NEW:
                        series_new();
                        break;
                    default:
                        break;
                }
                break;
            case VIEW_FILMS_LIST:
                switch (key) {
                    case KEY_ARROW_DOWN:
                        line_f++;
                        setView(view);
                        break;
                    case KEY_ARROW_UP:
                        line_f--;
                        setView(view);
                        break;
                    case KEY_REMOVE:
                        try {
                            db.remove(film_pool[line_f]);
                            film_pool -= line_f;
                            if (line_f >= film_pool.size()) line_f--;
                        } catch (std::invalid_argument &e) {
                            throw std::invalid_argument("Trying to delete invalid film.");
                        }
                        setView(view);
                        break;
                    case KEY_SORT:
                        film_pool.sort();
                        setView(view);
                        break;
                    case KEY_DETAILS:
                    case KEY_ENTER:
                        setView(VIEW_FILM);
                        break;
                    case KEY_NEW:
                        film_new();
                        break;
                    case KEY_EDIT:
                        edit(film_pool[line_f]);
                        db.write(film_pool[line_f]);
                        setView(VIEW_FILMS_LIST);
                        break;
                    default:
                        break;
                }
                break;
            case VIEW_PPVS_LIST:
                switch (key) {
                    case KEY_ARROW_DOWN:
                        line_p++;
                        setView(view);
                        break;
                    case KEY_ARROW_UP:
                        line_p--;
                        setView(view);
                        break;
                    case KEY_REMINDER:
                        ppv_pool[line_p].flipReminder();
                        db.write(ppv_pool[line_p]);
                        setView(view);
                        break;
                    case KEY_REMOVE:
                        try {
                            db.remove(ppv_pool[line_p]);
                            ppv_pool -= line_p;
                            if (line_p >= ppv_pool.size()) line_p--;
                        } catch (std::invalid_argument &e) {
                            throw std::invalid_argument("Trying to delete invalid ppv.");
                        }
                        setView(view);
                        break;
                    case KEY_SORT:
                        ppv_pool.sort();
                        setView(view);
                        break;
                    case KEY_DETAILS:
                    case KEY_ENTER:
                        setView(VIEW_PPV);
                        break;
                    case KEY_NEW:
                        ppv_new();
                        break;
                    case KEY_EDIT:
                        edit(ppv_pool[line_p]);
                        db.write(ppv_pool[line_p]);
                        setView(VIEW_PPVS_LIST);
                        break;
                    default:
                        break;
                }
                break;
            case VIEW_SERIES_FILTERED:
                switch (key) {
                    case KEY_QUIT:
                        return;
                    case KEY_ARROW_DOWN:
                        line_fs++;
                        setView(view);
                        break;
                    case KEY_ARROW_UP:
                        line_fs--;
                        setView(view);
                        break;
                    case KEY_FOLLOW:
                        filtered_unfollow();
                        break;
                    case KEY_REMOVE:
                    case KEY_DELETE:
                        try {
                            db.remove(*(filtered_pool[line_fs]));
                            series_pool -= *(filtered_pool[line_fs]);
                            filtered_pool = series_pool.filtered();
                            if (line_fs >= filtered_pool.size()) line_fs--;
                        } catch (std::invalid_argument &e) {}
                        if (filtered_pool.empty()) setView(VIEW_SERIES_LIST);
                        else setView(view);
                        break;
                    case KEY_SORT:
                        series_pool.sort();
                        filtered_pool = series_pool.filtered();
                        setView(view);
                        break;
                    case KEY_FILTER:
                        setView(VIEW_SERIES_LIST);
                        break;
                    case KEY_DETAILS:
                    case KEY_ENTER:
                        setView(VIEW_SERIES_F);
                        break;
                    case KEY_EDIT:
                        edit(filtered_pool[line_fs]);
                        db.write(filtered_pool[line_fs]);
                        filtered_pool = series_pool.filtered();
                        setView(VIEW_SERIES_FILTERED);
                    case KEY_NEW: {
                        series_new();
                        break;
                    }
                    default:
                        break;
                }
                break;
            case VIEW_SERIES:
                setView(VIEW_SERIES_LIST);
                break;
            case VIEW_FILM:
                setView(VIEW_FILMS_LIST);
                break;
            case VIEW_PPV:
                setView(VIEW_PPVS_LIST);
                break;
            case VIEW_SERIES_F:
                setView(VIEW_SERIES_FILTERED);
                break;
            default:
                break;
        }
    }
}

void Interface::filtered_unfollow() {
    filtered_pool[line_fs]->flipFollow();
    db.write(*(filtered_pool[line_fs]));
    line_fs--;
    filtered_pool = series_pool.filtered();
    if (filtered_pool.empty()) setView(VIEW_SERIES_LIST);
    else setView(view);
}

void Interface::ppv_new() {
    Ppv n;
    edit(n);
    if (!n.getTitle().empty() && n.getTitle().find_first_not_of(' ') != std::string::npos) {
        ppv_pool += n;
        db.write(n);
    }
    setView(VIEW_PPVS_LIST);
}

void Interface::film_new() {
    Film n;
    edit(n);
    if (!n.getTitle().empty() && n.getTitle().find_first_not_of(' ') != std::string::npos) {
        film_pool += n;
        db.write(n);
    }
    setView(VIEW_FILMS_LIST);
}

void Interface::series_filter() {
    filtered_pool = series_pool.filtered();
    line_fs = 0;
    if (!filtered_pool.empty()) setView(VIEW_SERIES_FILTERED);
    else printError("No series followed.");
}

void Interface::series_new() {
    Series n;
    edit(n);
    if (!n.getTitle().empty() && n.getTitle().find_first_not_of(' ') != std::string::npos) {
        series_pool += n;
        db.write(n);
    }
    setView(VIEW_SERIES_LIST);
}

void Interface::setView(unsigned short view) {
    Interface::view = view;
    clear();
    render();
}

void Interface::details(const Piece *p, int active_line = -1) {
    int size = 0;
    std::string *attrs = nullptr;
    if (typeid(*p) == typeid(Series)) {
        size = SERIES_DETAILS_NO;
        attrs = new std::string[SERIES_DETAILS_NO]SERIES_DETAILS;
    } else if (typeid(*p) == typeid(Film)) {
        size = FILM_DETAILS_NO;
        attrs = new std::string[FILM_DETAILS_NO]FILM_DETAILS;
    } else if (typeid(*p) == typeid(Ppv)) {
        size = PPV_DETAILS_NO;
        attrs = new std::string[PPV_DETAILS_NO]PPV_DETAILS;
    } else {
        throw std::runtime_error("Incorrect type passed to details.");
    }
    int j = 0;
    auto piece_details = p->getDetails();
    move(0, 0);
    for (int i = 0; i < size; ++i) {
        attron(A_BOLD);
        printw(attrs[i].c_str());
        printw(":");
        move(getcury(stdscr), DETAILS_TAB);
        attroff(A_BOLD);
        attron(COLOR_PAIR(j == active_line ? 6 : 5));
        printw(piece_details[attrs[i]].c_str());
        printw("\n");
        attroff(COLOR_PAIR(j == active_line ? 6 : 5));
        ++j;
    }
    delete[] attrs;
}

template<typename T>
void Interface::list(Pool<T> &pool, unsigned int activeLine, unsigned int start_line) {
    _list(pool, activeLine, start_line);
}

template<typename T>
void Interface::edit(T &piece) {
    std::string *attrs = nullptr;
    int *types = nullptr;
    if (typeid(T) == typeid(Series)) {
        attrs = new std::string[SERIES_DETAILS_NO]SERIES_DETAILS;
        types = new int[SERIES_DETAILS_NO]SERIES_DETAILS_TYPES;
    } else if (typeid(T) == typeid(Film)) {
        attrs = new std::string[FILM_DETAILS_NO]FILM_DETAILS;
        types = new int[FILM_DETAILS_NO]FILM_DETAILS_TYPES;
    } else if (typeid(T) == typeid(Ppv)) {
        attrs = new std::string[PPV_DETAILS_NO]PPV_DETAILS;
        types = new int[PPV_DETAILS_NO]PPV_DETAILS_TYPES;
    } else {
        throw std::runtime_error("Incorrect type passed to editor.");
    }


    bool insert_mode = false, endwhile = false;
    std::string insert;
    auto piece_details = piece.getDetails();
    auto line = Counter(piece_details.size());
    char buff[1];
    //unsigned short last_view = view;
    setView(VIEW_EDIT);
    int key = 0;
    do {
        if (!insert_mode) {
            switch (key) {
                case KEY_ESC:
                case KEY_BACKSPACE:
                    //setView(last_view);
                    endwhile = true;
                    break;
                case KEY_ARROW_LEFT:
                    switch (types[line]) {
                        case TYPE_DATE:
                            try {
                                auto m = std::get<time_t *>(piece[attrs[line]]);
                                *m -= 60;
                                piece_details = piece.getDetails();
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                            break;
                        case TYPE_INT:
                            try {
                                auto m = std::get<unsigned short *>(piece[attrs[line]]);
                                (*m)--;
                                piece_details = piece.getDetails();
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                            break;
                        case TYPE_FLOAT:
                            try {
                                auto m = std::get<float *>(piece[attrs[line]]);
                                (*m) -= 0.1;
                                piece_details = piece.getDetails();
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                            break;
                        case TYPE_WEEKDAY:
                            try {
                                auto m = std::get<unsigned short *>(piece[attrs[line]]);
                                *m = (*m - 1) >= 0 ? (*m - 1) % 7 : 6;
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                            break;
                    }
                    break;
                case KEY_ARROW_RIGHT:
                    switch (types[line]) {
                        case TYPE_DATE:
                            try {
                                auto m = std::get<time_t *>(piece[attrs[line]]);
                                *m += 60;
                                piece_details = piece.getDetails();
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                            break;
                        case TYPE_INT:
                            try {
                                auto m = std::get<unsigned short *>(piece[attrs[line]]);
                                (*m)++;
                                piece_details = piece.getDetails();
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                            break;
                        case TYPE_FLOAT:
                            try {
                                auto m = std::get<float *>(piece[attrs[line]]);
                                (*m) += 0.1;
                                piece_details = piece.getDetails();
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                            break;
                        case TYPE_WEEKDAY:
                            try {
                                auto m = std::get<unsigned short *>(piece[attrs[line]]);
                                *m = (*m + 1) % 7;
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                            break;
                    }
                    break;
                case KEY_ARROW_DOWN:
                    line++;
                    break;
                case KEY_ARROW_UP:
                    line--;
                    break;
                case KEY_EDIT:
                case KEY_ENTER:
                    switch (types[line]) {
                        case TYPE_STRING:
                        case TYPE_INT:
                        case TYPE_FLOAT:
                            move(line, DETAILS_TAB);
                            attron(COLOR_PAIR(6));
                            for (int i = 0; i < piece_details[attrs[line]].size(); ++i) mvdelch(line, DETAILS_TAB);
                            move(line, DETAILS_TAB);
                            insert = "";
                            insert_mode = true;
                            continue;
                        case TYPE_BOOL:
                            try {
                                auto m = std::get<bool *>(piece[attrs[line]]);
                                *m = !*m;
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                            break;
                        case TYPE_WEEKDAY:
                            try {
                                auto m = std::get<unsigned short *>(piece[attrs[line]]);
                                *m = (*m + 1) % 7;
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                            break;
                        case TYPE_DATE:
                            try {
                                auto m = std::get<time_t *>(piece[attrs[line]]);
                                *m = time(nullptr);
                                piece_details = piece.getDetails();
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            }
                    }
                default:
                    break;
            }
            details(&piece, line);
        } else {
            switch (key) {
                case KEY_ENTER:
                    switch (types[line]) {
                        case TYPE_STRING:
                            if (!insert.empty()) {
                                try {
                                    auto a = std::get<std::string *>(piece[attrs[line]]);
                                    a->clear();
                                    *a = insert;
                                    piece_details[attrs[line]] = insert;
                                } catch (std::bad_variant_access &e) {
                                    throw std::runtime_error("Inconsistent parameter type in edit.");
                                }
                            }
                            break;
                        case TYPE_INT:
                            try {
                                auto a = std::get<unsigned short *>(piece[attrs[line]]);
                                unsigned long i = std::stoul(insert);
                                if (std::to_string(i) == insert && i >= 0 && i < MAX_SHORT) {
                                    *a = static_cast<unsigned short>(i);
                                    piece_details[attrs[line]] = insert;
                                }
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            } catch (std::invalid_argument &e) {
                                printError("Insert only non-negative integers!");
                            }
                            break;
                        case TYPE_FLOAT:
                            try {
                                auto a = std::get<float *>(piece[attrs[line]]);
                                float i = std::stof(insert);
                                std::stringstream ss;
                                ss << std::fixed << std::setprecision(1) << i;
                                if (i >= 0 && ss.str() == insert) {
                                    *a = i;
                                    piece_details = piece.getDetails();
                                } else throw std::invalid_argument("Invalid float.");
                            } catch (std::bad_variant_access &e) {
                                throw std::runtime_error("Inconsistent parameter type in edit.");
                            } catch (std::invalid_argument &e) {
                                printError("Insert only >=0 floats with dot as decimal point.");
                            }
                            break;
                        default:
                            break;
                    }
                case KEY_ESC:
                case KEY_BACKSPACE:
                    insert_mode = false;
                    attroff(COLOR_PAIR(6));
                    details(&piece, line);
                    break;
                case KEY_ARROW_LEFT:
                    if (getcurx(stdscr) > DETAILS_TAB) {
                        mvdelch(line, getcurx(stdscr) - 1);
                        insert.erase(insert.end() - 1);
                    }
                    break;
                default:
                    buff[0] = static_cast<char>(key);
                    printw(buff);
                    insert += static_cast<char>(key);
                    break;
            }
        }
    } while ((!endwhile && (key = getch())));
    delete[] attrs;
    delete[] types;
}

void Interface::edit(Series *&piece) {
    edit(*piece);
}

void Interface::printError(std::string error) const {
    attron(A_BOLD | COLOR_PAIR(6));
    mvprintw(max_y - 1, 0, error.c_str());
    attroff(A_BOLD | COLOR_PAIR(6));
}

Interface::Counter::Counter(unsigned int max) : max(max) {}

void Interface::Counter::operator++(int) {
    if (i + 1 < max) ++i;
}

void Interface::Counter::operator--(int) {
    if (i) --i;
}

Interface::Counter::operator unsigned int() {
    return i;
}

Interface::Counter::operator int() {
    return i;
}

Interface::Counter::operator unsigned long() {
    return i;
}

Interface::Counter::operator long int() {
    return i;
}

template<typename T>
Interface::LineCounter<T>::LineCounter(std::vector<T> *p) : p(p) {}

template<typename T>
Interface::LineCounter<T>::operator unsigned int() const {
    return i;
}

template<typename T>
void Interface::LineCounter<T>::operator++(int) {
    if (i + 1 < p->size()) {
        i++;
        if (max_y - 3 + start_line <= i) start_line++;
    }
}

template<typename T>
void Interface::LineCounter<T>::operator--(int) {
    if (i > 0) i--;
    if (i < start_line) start_line--;
}

template<typename T>
Interface::LineCounter<T> &Interface::LineCounter<T>::operator=(unsigned int s) {
    i = s;
    return *this;
}

template<typename T>
unsigned int Interface::LineCounter<T>::getStartLine() const {
    return start_line;
}