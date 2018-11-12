//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_INTERFACE_HPP
#define SERIESTRACKER_INTERFACE_HPP

#include <ncurses.h>        // Order of those
#include "constants.hpp"    // two is important.
#include "Database.hpp"
#include "Series.hpp"
#include "Film.hpp"
#include "Ppv.hpp"
#include "Pool.hpp"
#include "Pool.cpp"


/*!
 * Provides whole communication between human and the program.
 */
class Interface {
private:
    /*!
     * Provides ability to count within 0 to max boundaries.
     */
    class Counter {
    private:
        unsigned int i = 0, max = 0;
    public:
        explicit Counter(unsigned int max);

        operator unsigned int();

        operator int();

        operator long int();

        operator unsigned long();

        void operator++(int);

        void operator--(int);
    };

    /*!
     * Provides ability to count within 0 to .size() of a vector<T>, stored as inner pointer.
     * Also calculates from which element should interface start showing list, so active element remains always on screen.
     * @tparam T type of elements in the vector<> which size determines counter max
     */
    template<typename T>
    class LineCounter {
    private:
        std::vector<T> *p;
        unsigned int i = 0;
        unsigned int start_line = 0;
        int max_y = getmaxy(stdscr);
    public:
        /*!
         * Calculates from which line start the listing, so the active line remains on the screen.
         * @return index: unsigned int
         */
        unsigned int getStartLine() const;

        LineCounter() = default;

        /*!
         * Initializes counter with maximum = parameter vector.size()
         * @param p vector which size is limiting counter
         */
        explicit LineCounter(std::vector<T> *p);

        operator unsigned int() const;

        void operator++(int);

        void operator--(int);

        LineCounter &operator=(unsigned int);
    };

    unsigned short view = 0;
    unsigned short max_y, max_x;
    Database db;
    Pool<Series> series_pool;
    LineCounter<Series> line_s;
    Pool<Series *> filtered_pool;
    LineCounter<Series *> line_fs;
    Pool<Film> film_pool;
    LineCounter<Film> line_f;
    Pool<Ppv> ppv_pool;
    LineCounter<Ppv> line_p;

    //! Prints welcome string in the middle of the screen
    void welcome();

    //! Prints line with tabs at the top of the screen
    void topKeys();

    //! Prints error (usually regarding user input) on the bottom of the screen
    //! @param error: std::string
    void printError(std::string) const;

    //! Sets menu state (view), and refreshing content.
    //! @param view
    void setView(unsigned short);

    /*!
     * Prints tabulated line in given color pair
     * @param color_pair: int
     * @param fields_count: int
     * @param columns_width: const int*
     * @param fields: const string*
     */
    void _colorLinePrint(int, int, const int[], const std::string[]) const;

    //! Providing view to edit Series* entry.
    //! @param series: Series*
    void edit(Series *&);

    /*!
     * Providing view to edit Piece entry.
     * @param piece: T
     * @tparam T: type of piece to edit
     */
    template<typename T>
    void edit(T &);

    template<typename T>
    void _list(Pool<T> &, unsigned int, unsigned int);

    void _list(Pool<Series *> &, unsigned int, unsigned int);

    /*!
     * Method is listing pieces from Pool given as argument, starting at @start_line, with active @active_line.
     * @tparam T: type of pieces in pool
     * @param pool: Pool<T>
     * @param active_line: unsigned int
     * @param start_line: unsigned int
     */
    template<typename T>
    void list(Pool<T> &, unsigned int, unsigned int);

    //! Prints line with usage hints for the user at the bottom of the screen, depending on current view.
    void bottomKeys();

    /*! Prints details of given @piece, with possible @active_line marked in different color.
     * @param piece: const Piece*
     * @param active_line: int
     */
    void details(const Piece *, int);

    //! Writes current view to terminal window.
    void render();

    //! Triggers adding a new series.
    void series_new();

    //! Triggers filtering of series to followed only.
    void series_filter();

    //! Triggers adding a new film.
    void film_new();

    //! Triggers adding a new ppv.
    void ppv_new();

    //! Performs unfollowing of a series in filtered view.
    void filtered_unfollow();

public:
    //! Getting user input and changing views accordingly.
    void mainLoop();

    Interface();

    ~Interface();
};

#endif //SERIESTRACKER_INTERFACE_HPP
