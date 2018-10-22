//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_INTERFACE_HPP
#define SERIESTRACKER_INTERFACE_HPP

#include <ncurses.h>
#include "Series.hpp"


class Interface {
public:
    Interface();

    void menu();

    void show_series(const Series &);

    void show_film(const Film &);

    void show_ppv(const Ppv &);

    virtual ~Interface();
};


#endif //SERIESTRACKER_INTERFACE_HPP
