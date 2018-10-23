//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_INTERFACE_HPP
#define SERIESTRACKER_INTERFACE_HPP

#include <ncurses.h>
#include "Series.hpp"
#include "Ppv.hpp"
#include "Pool.hpp"


class Interface {
private:
    unsigned short view = 0;
    unsigned short maxy, maxx;

    void welcome();

    void topkeys();

public:
    void _colorLinePrint(int, int, const int[], const std::string[]) const;

    void list(Pool<Series> &);

    void list(Pool<Film> &);

    void list(Pool<Ppv> &);

    void bottomkeys();

public:
    Interface();

    void menu();

    void show_series(const Series &);

    void show_film(const Film &);

    //void show_ppv(const Ppv &);



    virtual ~Interface();
};


#endif //SERIESTRACKER_INTERFACE_HPP
