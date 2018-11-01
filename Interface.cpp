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
    maxy = static_cast<unsigned short>getmaxy(stdscr);
    maxx = static_cast<unsigned short>getmaxx(stdscr);
    if (maxx < 60 || maxy < 5) throw std::runtime_error("Terminal window too small.");
    if (!has_colors()) throw std::runtime_error("Terminal doesn't support colors.");
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_RED, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_CYAN);
    line_s = LineCounter<Series>(&series_pool);
    line_f = LineCounter<Film>(&film_pool);
    //Constructing pool
    //Pool<Series> series_pool;
    //std::cout << series_pool.sorted()[0];
    series_pool += Series("Dexter", "Very interesting series about killing.", 43, 89, 7, "Drama");
    series_pool += Series("Chuck", "Series about computers and CIA", 22, 90, 4, "CIA");
    series_pool[0].follow();
    film_pool += Film("Dexter", "Very interesting series about killing.", 43, 89, "Drama");
    film_pool += Film("Chuck", "Series about computers and CIA", 22, 90, "CIA");
    ppv_pool += Ppv("Chuck", "Series about computers and CIA", 22, 90, 143124312);
}

void Interface::topkeys() {
    const char *entries[] = {"F1: Series", "F2: Films", "F3: PPVs"};
    attron(A_BOLD);
    move(0, 0);
    for (unsigned short i = 0; i < 3; i++) {
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

Interface::~Interface() {
    endwin();
}

void Interface::menu() {
    topkeys();
    switch (view) {
        case 0:
            welcome();
            break;
        case 1:
            list(series_pool, line_s);
            break;
        case 2:
            list(film_pool, line_f);
            break;
        case 3:
            list(ppv_pool, line_p);
            break;
    }

}

void Interface::welcome() {
    const std::string welcomestr = "Welcome to SeriesTracker. Use keys as shown above and below to navigate.";
    mvprintw(maxy / 2, (maxx - static_cast<int>(welcomestr.length())) / 2, welcomestr.c_str());
}

void Interface::list(Pool<Series> &pool, int active_line) {
    const int columns_width[SERIES_LIST_PARAMS] = {maxx - 50, 28, 12, 10};
    const std::string fields[SERIES_LIST_PARAMS] = {"Title", "Genre", "Grade", "Followed"};
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

void Interface::list(Pool<Film> &pool, int active_line) {
    const int columns_width[FILM_LIST_PARAMS] = {maxx - 50, 38, 12};
    const std::string fields[FILM_LIST_PARAMS] = {"Title", "Genre", "Grade"};
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
    const int columns_width[PPV_LIST_PARAMS] = {maxx - 68, 28, 30, 10};
    const std::string fields[PPV_LIST_PARAMS] = {"Title", "Price", "Date", "Reminder"};
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
    topkeys();
    welcome();
    int key = 0;
    while ((key = getch())) {
        topkeys();
        switch (key) {
            case 266:
                setView(1);
                break;
            case 267:
                setView(2);
                break;
            case 268:
                setView(3);
                break;
        }
        switch (view) {
            case 0:
            case 1:
                switch (key) {
                    case 258:
                        line_s++;
                        setView(1);
                        break;
                    case 259:
                        line_s--;
                        setView(1);
                        break;
                }
                break;
            case 2:
                switch (key) {
                    case 258:
                        line_f++;
                        setView(2);
                        break;
                    case 259:
                        line_f--;
                        setView(2);
                        break;
                }
                break;
            case 3:
                break;

        }

        //printw("%d", c);
    }
}

void Interface::setView(unsigned short view) {
    Interface::view = view;
    clear();
    menu();
}

