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
    line_s = LineCounter<Series>(&series_pool);
    line_fs = LineCounter<Series *>(&filtered_pool);
    line_f = LineCounter<Film>(&film_pool);
    line_p = LineCounter<Ppv>(&ppv_pool);
    series_pool += Series("Dexter", "Very interesting series about killing.", 43, 89, 7, "Drama");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool[0].sfollow();
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

void Interface::menu() {
    topKeys();
    bottomKeys();
    switch (view) {
        case VIEW_WELCOME:
            welcome();
            break;
        case VIEW_SERIES_LIST:
            list(series_pool, line_s);
            break;
        case VIEW_FILMS_LIST:
            list(film_pool, line_f);
            break;
        case VIEW_PPVS_LIST:
            list(ppv_pool, line_p);
            break;
        case VIEW_SERIES_FILTERED:
            list(filtered_pool, line_fs);
            break;
        default:
            break;
    }

}

void Interface::welcome() {
    const std::string welcome_string = WELCOME_STRING;
    mvprintw(max_y / 2, (max_x - static_cast<int>(welcome_string.length())) / 2, welcome_string.c_str());
}

void Interface::list(Pool<Series> &pool, int active_line) {
    const int columns_width[SERIES_LIST_PARAMS] = SERIES_LIST_PARAMS_WIDTHS;
    const std::string fields[SERIES_LIST_PARAMS] = SERIES_LIST_PARAMS_HEADERS;
    move(1, 0);
    _colorLinePrint(2, SERIES_LIST_PARAMS, columns_width, fields);
    unsigned int i = 0;
    for (auto &line: pool) {
        if (i == active_line) attron(COLOR_PAIR(4));
        _colorLinePrint(0, SERIES_LIST_PARAMS, columns_width, line.getListParams().data());
        if (i == active_line) attroff(COLOR_PAIR(4));
        i++;
    }
}

void Interface::list(Pool<Series *> &pool, int active_line) {
    const int columns_width[SERIES_LIST_PARAMS] = SERIES_LIST_PARAMS_WIDTHS;
    const std::string fields[SERIES_LIST_PARAMS] = SERIES_LIST_PARAMS_HEADERS;
    move(1, 0);
    _colorLinePrint(2, SERIES_LIST_PARAMS, columns_width, fields);
    unsigned int i = 0;
    for (auto &line: pool) {
        if (i == active_line) attron(COLOR_PAIR(4));
        _colorLinePrint(0, SERIES_LIST_PARAMS, columns_width, line->getListParams().data());
        if (i == active_line) attroff(COLOR_PAIR(4));
        i++;
    }
}

void Interface::list(Pool<Film> &pool, int active_line) {
    const int columns_width[FILM_LIST_PARAMS] = FILM_LIST_PARAMS_WIDTHS;
    const std::string fields[FILM_LIST_PARAMS] = FILM_LIST_PARAMS_HEADERS;
    move(1, 0);
    _colorLinePrint(2, FILM_LIST_PARAMS, columns_width, fields);
    unsigned int i = 0;
    for (auto &line: pool) {
        if (i == active_line) attron(COLOR_PAIR(4));
        _colorLinePrint(0, FILM_LIST_PARAMS, columns_width, line.getListParams().data());
        if (i == active_line) attroff(COLOR_PAIR(4));
        i++;
    }
}

void Interface::list(Pool<Ppv> &pool, int active_line) {
    const int columns_width[PPV_LIST_PARAMS] = PPV_LIST_PARAMS_WIDTHS;
    const std::string fields[PPV_LIST_PARAMS] = PPV_LIST_PARAMS_HEADERS;
    move(1, 0);
    _colorLinePrint(2, PPV_LIST_PARAMS, columns_width, fields);
    unsigned int i = 0;
    for (auto &line: pool) {
        if (i == active_line) attron(COLOR_PAIR(4));
        _colorLinePrint(0, PPV_LIST_PARAMS, columns_width, line.getListParams().data());
        if (i == active_line) attroff(COLOR_PAIR(4));
        i++;
    }
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
    menu();
    int key = 0;
    while ((key = getch())) {
        menu();
        switch (key) {
            case KEY_SERIES_LIST:
                setView(VIEW_SERIES_LIST);
                break;
            case KEY_FILMS_LIST:
                setView(VIEW_FILMS_LIST);
                break;
            case KEY_PPVS_LIST:
                setView(VIEW_FILMS_LIST);
                break;
            case KEY_QUIT:
                endwin();
                exit(0);
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
                        series_pool[line_s].sfollow();
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
                        ppv_pool[line_p].setReminder(!ppv_pool[line_p].isReminder());
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
                        filtered_pool[line_fs]->sfollow();
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
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        setView(view);
    }
}

void Interface::setView(unsigned short view) {
    Interface::view = view;
    clear();
    menu();
}

