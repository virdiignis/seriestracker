//
// Created by prance on 22.10.18.
//

#include <iostream>
#include "Interface.hpp"

Interface::Interface() {
    initscr();
    keypad(stdscr, true);
    noecho();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_RED, COLOR_GREEN);
    maxy = static_cast<unsigned short>getmaxy(stdscr);
    maxx = static_cast<unsigned short>getmaxx(stdscr);
}


void Interface::topline() {
    const char *entries[] = {"F1: Series", "F2: Films", "F3: PPVs"};
    attron(A_BOLD | COLOR_PAIR(1));
    for (unsigned short i = 0; i < 3; i++) {
        if (view == i + 1) attron(COLOR_PAIR(3));
        printw(entries[i]);
        if (view == i + 1) attron(COLOR_PAIR(1));
        printw("\t");
    }
    attroff(A_BOLD | COLOR_PAIR(1));
}


Interface::~Interface() {
    endwin();
}

void Interface::menu() {
    topline();
    welcome();
    int c;
    while (c = getch()) {
        view = c - 264;
        //printw("%d", c);
        clear();
        topline();
    }
}

void Interface::welcome() {
    const std::string welcomestr = "Welcome to SeriesTracker. Use keys as shown above and below to navigate.";
    mvprintw(maxy / 2, maxx / 2 - static_cast<int>(welcomestr.length()) / 2, welcomestr.c_str());
}
