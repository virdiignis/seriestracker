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
    class Counter {
    private:
        unsigned int i = 0, max = 0;
    public:
        explicit Counter(unsigned int max);

        operator unsigned int();

        operator int();

        operator unsigned long();

        void operator++(int);

        void operator--(int);
    };

    template<typename T>
    class LineCounter {
    private:
        std::vector<T> *p;
        unsigned int i = 0;
        unsigned int start_line = 0;
        int max_y = getmaxy(stdscr);
    public:
        unsigned int
        getStartLine() const; //TODO... można to przepisać na rzutowanie do std::pair w szczeŋólnych przyapdkach i zmienić funkcje list interfejsu.

        LineCounter() = default;

        explicit LineCounter(std::vector<T> *p);

        operator unsigned int() const;

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

    void _edit(Series *&);

    template<typename T>
    void _edit(T &);

    template<typename T>
    void _list(Pool<T> &, unsigned int, unsigned int);

    void _list(Pool<Series *> &, unsigned int, unsigned int);

    template<typename T>
    void list(Pool<T> &, unsigned int, unsigned int);

    void bottomKeys();

    void details(const Piece *, int active_line);

    void render();

public:
    void mainLoop();

    Interface();

    ~Interface();
};

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

#endif //SERIESTRACKER_INTERFACE_HPP
