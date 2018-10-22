//
// Created by prance on 22.10.18.
//

#include "Interface.hpp"

Interface::Interface() {
    initscr();
    keypad(stdscr, true);
    noecho();
}

Interface::~Interface() {
    endwin();
}
