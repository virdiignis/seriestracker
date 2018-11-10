//
// Created by prance on 22.10.18.
//

#include <iostream>
#include "Interface.hpp"
#include "Pool.cpp"


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
    line_s = LineCounter<Series>(&series_pool);
    line_fs = LineCounter<Series *>(&filtered_pool);
    line_f = LineCounter<Film>(&film_pool);
    line_p = LineCounter<Ppv>(&ppv_pool);
    series_pool += Series("Dexter", "Very interesting series about killing.", 43, 89, 6, "Drama");
    series_pool += Series("Dexter", "Very interesting series about killing.", 43, 89, 6, "Drama");
    series_pool += Series("Dexter", "Very interesting series about killing.", 43, 89, 6, "Drama");
    series_pool += Series("Dexter", "Very interesting series about killing.", 43, 89, 6, "Drama");
    series_pool += Series("Dexter", "Very interesting series about killing.", 43, 89, 6, "Drama");
    series_pool += Series("Dexter", "Very interesting series about killing.", 43, 89, 6, "Drama");
    series_pool += Series("Dexter", "Very interesting series about killing.", 43, 89, 6, "Drama");
    series_pool += Series("Dexter", "Very interesting series about killing.", 43, 89, 6, "Drama");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    //TODO... zakres rysowania :/
    series_pool[0].switchFollow();
    film_pool += Film("Dexter", "Very interesting series about killing.", 43, 89, "Drama");
    film_pool += Film("Chuck", "Series about computers and CIA", 22, 90, "CIA");
    ppv_pool += Ppv("Chuck", "Series about computers and CIA", 22, 90, 1541523251);
    ppv_pool += Ppv("Chuck", "Series about computers and CIA", 22, 90, 1541523000);
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
        default:
            delete[] entries;
            delete[] width;
            return;
    }

    move(max_y - 1, 0);
    attron(A_BOLD);
    _colorLinePrint(3, entries_num, width, entries);
    attroff(A_BOLD);


//    attron(A_BOLD | COLOR_PAIR(3));

//    for (auto &entrie : entries) {
//        printw(entrie);
//        //printw("\t");
//    }
//    attroff(A_BOLD | COLOR_PAIR(3));
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
            details(&(series_pool[line_s]));
            break;
        case VIEW_SERIES_F:
            details(filtered_pool[line_fs]);
            break;
        case VIEW_FILM:
            details(&(film_pool[line_f]));
            break;
        case VIEW_PPV:
            details(&(ppv_pool[line_p]));
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
    for (int k = start_line; k < start_line + max_y - 3; ++k) {
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
    for (int k = start_line; k < start_line + max_y - 3; ++k) {
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
        switch (key) {
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
            case VIEW_SERIES_LIST:
                switch (key) {
                    case KEY_ARROW_DOWN:
                        line_s++;
                        break;
                    case KEY_ARROW_UP:
                        line_s--;
                        break;
                    case KEY_FOLLOW:
                        series_pool[line_s].switchFollow();
                        break;
                    case KEY_REMOVE:
                        try {
                            series_pool -= line_s;
                            if (line_s >= series_pool.size()) line_s--;
                        } catch (std::invalid_argument &e) {}
                        break;
                    case KEY_SORT:
                        series_pool.sort();
                        break;
                    case KEY_FILTER:
                        filtered_pool = series_pool.filtered();
                        if (!filtered_pool.empty()) setView(VIEW_SERIES_FILTERED);
                        break;
                    case KEY_DETAILS:
                        setView(VIEW_SERIES);
                    default:
                        break;
                }
                break;
            case VIEW_FILMS_LIST:
                switch (key) {
                    case KEY_ARROW_DOWN:
                        line_f++;
                        break;
                    case KEY_ARROW_UP:
                        line_f--;
                        break;
                    case KEY_REMOVE:
                        try {
                            film_pool -= line_f;
                            if (line_f >= film_pool.size()) line_f--;
                        } catch (std::invalid_argument &e) {}
                        break;
                    case KEY_SORT:
                        film_pool.sort();
                        break;
                    case KEY_DETAILS:
                        setView(VIEW_FILM);
                    default:
                        break;
                }
                break;
            case VIEW_PPVS_LIST:
                switch (key) {
                    case KEY_ARROW_DOWN:
                        line_p++;
                        break;
                    case KEY_ARROW_UP:
                        line_p--;
                        break;
                    case KEY_REMINDER:
                        ppv_pool[line_p].flipReminder();
                        break;
                    case KEY_REMOVE:
                        try {
                            ppv_pool -= line_p;
                            if (line_p >= ppv_pool.size()) line_p--;
                        } catch (std::invalid_argument &e) {}
                        break;
                    case KEY_SORT:
                        ppv_pool.sort();
                        break;
                    case KEY_DETAILS:
                        setView(VIEW_PPV);
                    default:
                        break;
                }
                break;
            case VIEW_SERIES_FILTERED:
                switch (key) {
                    case KEY_ARROW_DOWN:
                        line_fs++;
                        break;
                    case KEY_ARROW_UP:
                        line_fs--;
                        break;
                    case KEY_FOLLOW:
                        filtered_pool[line_fs]->switchFollow();
                        line_fs--;
                        filtered_pool = series_pool.filtered();
                        if (filtered_pool.empty()) setView(VIEW_SERIES_LIST);
                        break;
                    case KEY_REMOVE:
                        try {
                            series_pool -= *filtered_pool[line_fs];
                            filtered_pool -= line_fs;
                            if (line_fs >= filtered_pool.size()) line_fs--;
                        } catch (std::invalid_argument &e) {}
                        break;
                    case KEY_SORT:
                        filtered_pool.sort();
                        series_pool.sort();
                        break;
                    case KEY_FILTER:
                        setView(VIEW_SERIES_LIST);
                        break;
                    case KEY_DETAILS:
                        setView(VIEW_SERIES_F);
                    default:
                        break;
                }
                break;
            case VIEW_SERIES:
                switch (key) {
                    case KEY_DETAILS:
                        setView(VIEW_SERIES_LIST);
                        break;
                }
                break;
            case VIEW_FILM:
                switch (key) {
                    case KEY_DETAILS:
                        setView(VIEW_FILMS_LIST);
                        break;
                }
                break;
            case VIEW_PPV:
                switch (key) {
                    case KEY_DETAILS:
                        setView(VIEW_PPVS_LIST);
                        break;
                }
                break;
            case VIEW_SERIES_F:
                switch (key) {
                    case KEY_DETAILS:
                        setView(VIEW_SERIES_FILTERED);
                        break;
                }
                break;
            default:
                break;
        } //TODO ppv implementation of getDetails, and enter to details and return from details for filtred series
        setView(view);
    }
}

void Interface::setView(unsigned short view) {
    Interface::view = view;
    clear();
    render();
}

void Interface::details(const Piece *p) {
    move(0, 0);
    for (auto &entry: p->getDetails()) {
        attron(A_BOLD);
        printw(entry.first.c_str());
        printw(":");
        move(getcury(stdscr), 25);
        attroff(A_BOLD);
        attron(COLOR_PAIR(5));
        printw(entry.second.c_str());
        printw("\n");
        attroff(COLOR_PAIR(5));
    }
}

template<typename T>
void Interface::list(Pool<T> &pool, unsigned int activeLine, unsigned int start_line) {
    _list(pool, activeLine, start_line);
}

