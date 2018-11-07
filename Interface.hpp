//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_INTERFACE_HPP
#define SERIESTRACKER_INTERFACE_HPP

#include "constants.hpp"
#include <ncurses.h>
#include "Series.hpp"
#include "Ppv.hpp"
#include "Pool.hpp"


class Interface {
private:
    template<typename T>
    class LineCounter {
    private:
        unsigned int i = 0;
        Pool<T> *p;
    public:
        LineCounter() = default;

        explicit LineCounter(Pool<T> *p);

        operator int() const;

        void operator++(int);

        void operator--(int);

        LineCounter &operator=(unsigned int);
    };
    unsigned short view = 0;
    unsigned short max_y, max_x;
    Pool<Series> series_pool;
    LineCounter<Series> line_s;
    Pool<Series *> filtered_pool;
    LineCounter<Series *> line_fs;
    Pool<Film> film_pool;
    LineCounter<Film> line_f;
    Pool<Ppv> ppv_pool;
    LineCounter<Ppv> line_p;

    void welcome();

    void topKeys();

    void setView(unsigned short view);

    void _colorLinePrint(int, int, const int[], const std::string[]) const;

    void list(Pool<Series> &, int);

    void list(Pool<Series *> &, int);

    void list(Pool<Film> &, int);

    void list(Pool<Ppv> &, int);

    void bottomKeys();

    void details(const Piece *);

    void render();

public:
    void mainLoop();

    Interface();

    ~Interface();
};

template<typename T>
Interface::LineCounter<T>::LineCounter(Pool<T> *p) : p(p) {}

template<typename T>
Interface::LineCounter<T>::operator int() const {
    return i;
}

template<typename T>
void Interface::LineCounter<T>::operator++(int) {
    if (i + 1 < p->size()) i++;
}

template<typename T>
void Interface::LineCounter<T>::operator--(int) {
    if (i > 0) i--;
}

template<typename T>
Interface::LineCounter<T> &Interface::LineCounter<T>::operator=(unsigned int s) {
    i = s;
    return *this;
}


#endif //SERIESTRACKER_INTERFACE_HPP
