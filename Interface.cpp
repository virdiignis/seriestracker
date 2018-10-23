//
// Created by prance on 22.10.18.
//

#include <iostream>
#include "Interface.hpp"

Interface::Interface() {
    initscr();
    keypad(stdscr, true);
    noecho();
    maxy = static_cast<unsigned short>getmaxy(stdscr);
    maxx = static_cast<unsigned short>getmaxx(stdscr);
    if (maxx < 60 || maxy < 5) throw std::runtime_error("Terminal window too small.");
    if (!has_colors()) throw std::runtime_error("Terminal doesn't support colors.");
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_RED, COLOR_GREEN);
}


void Interface::topkeys() {
    const char *entries[] = {"F1: Series", "F2: Films", "F3: PPVs"};
    attron(A_BOLD | COLOR_PAIR(1));
    move(0, 0);
    for (unsigned short i = 0; i < 3; i++) {
        printw("\t");
        if (view == i + 1) attron(COLOR_PAIR(3));
        printw(entries[i]);
        if (view == i + 1) attron(COLOR_PAIR(1));
    }
    attroff(A_BOLD | COLOR_PAIR(1));
}


Interface::~Interface() {
    endwin();
}

void Interface::menu() {
    topkeys();
    welcome();
    int c;
    while ((c = getch())) {
        view = static_cast<unsigned short>(c - 264);
        //printw("%d", c);
        clear();
        topkeys();
    }
}

void Interface::welcome() {
    const std::string welcomestr = "Welcome to SeriesTracker. Use keys as shown above and below to navigate.";
    mvprintw(maxy / 2, (maxx - static_cast<int>(welcomestr.length())) / 2, welcomestr.c_str());
}

void Interface::list(Pool<Series> &pool) {
    const unsigned short fields_count = 4;
    const int columns_width[fields_count] = {maxx - 50, 28, 12, 10};
    const std::string fields[fields_count] = {"Title", "Genre", "Grade", "Followed"};
    move(1, 0);
    _colorLinePrint(2, fields_count, columns_width, fields);
    _colorLinePrint(0, fields_count, columns_width, pool[0].getListParams().data());

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