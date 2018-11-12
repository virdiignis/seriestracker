//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_DATABASE_HPP
#define SERIESTRACKER_DATABASE_HPP

#include "constants.hpp"
#include <string>
#include <fstream>
#include <filesystem>
#include <variant>
#include "Series.hpp"
#include "Pool.hpp"
#include "Ppv.hpp"

namespace fs = std::filesystem;

/*!
 * Provides interface for loading folder structure to Pools,
 * and for updating piecies back into the files.
 */
class Database {
private:
    /*!
     * Initializes the directories structure when program is run for the first time.
     */
    void start() const;

    /*!
     * Loads all of pieces specific for a Pool type into it.
     * @tparam T is type of Pieces stored in the pool.
     * @param pool of T-type pieces.
     */
    template<typename T>
    void load(Pool<T> &) const;

public:
    Database() = default;

    /*!
     * @param series pool
     * @param films pool
     * @param ppv's pool
     */
    Database(Pool<Series> &, Pool<Film> &, Pool<Ppv> &);

    /*!
     * Writes object given as Series* to disk.
     */
    void write(Series *&) const;

    /*!
     * Writes piece of T type to disk.
     * @tparam T type of piece to write to disk
     * @param piece to write to disk
     */
    template<typename T>
    void write(T &) const;

    /*!
     * Removes disk copy of given piece.
     * @tparam T type of piece to remove from disk
     * @param piece to be removed
     */
    template<typename T>
    void remove(T &) const;

};

template<typename T>
void Database::write(T &piece) const {
    int size = 0;
    std::string *attrs = nullptr;
    int *types = nullptr;
    std::string dir;
    if (typeid(T) == typeid(Series)) {
        size = SERIES_DETAILS_NO;
        dir = SERIES_DIR;
        types = new int[SERIES_DETAILS_NO]SERIES_DETAILS_TYPES;
        attrs = new std::string[SERIES_DETAILS_NO]SERIES_DETAILS;
    } else if (typeid(T) == typeid(Film)) {
        size = FILM_DETAILS_NO;
        dir = FILMS_DIR;
        types = new int[FILM_DETAILS_NO]FILM_DETAILS_TYPES;
        attrs = new std::string[FILM_DETAILS_NO]FILM_DETAILS;
    } else if (typeid(T) == typeid(Ppv)) {
        size = PPV_DETAILS_NO;
        dir = PPVS_DIR;
        types = new int[PPV_DETAILS_NO]PPV_DETAILS_TYPES;
        attrs = new std::string[PPV_DETAILS_NO]PPV_DETAILS;
    } else {
        throw std::runtime_error("Incorrect type passed to db_write.");
    }


    std::ofstream f(dir + piece.getTitle());
    if (!f.good()) throw std::runtime_error("Cannot open db file.");
    for (int i = 0; i < size; ++i) {
        switch (types[i]) {
            case TYPE_STRING:
                try {
                    f << ";" << *std::get<std::string *>(piece[attrs[i]]) << std::endl;
                } catch (std::bad_variant_access &e) {
                    throw std::runtime_error("Invalid types in db_write/string");
                }
                break;
            case TYPE_WEEKDAY:
            case TYPE_INT:
                try {
                    f << ";" << *std::get<unsigned short *>(piece[attrs[i]]) << std::endl;
                } catch (std::bad_variant_access &e) {
                    throw std::runtime_error("Invalid types in db_write/weekday/int");
                }
                break;
            case TYPE_DATE:
                try {
                    f << ";" << *std::get<time_t *>(piece[attrs[i]]) << std::endl;
                } catch (std::bad_variant_access &e) {
                    throw std::runtime_error("Invalid types in db_write/date");
                }
                break;
            case TYPE_FLOAT:
                try {
                    f << ";" << *std::get<float *>(piece[attrs[i]]) << std::endl;
                } catch (std::bad_variant_access &e) {
                    throw std::runtime_error("Invalid types in db_write/float");
                }
                break;
            case TYPE_BOOL:
                try {
                    f << ";" << *std::get<bool *>(piece[attrs[i]]) << std::endl;
                } catch (std::bad_variant_access &e) {
                    throw std::runtime_error("Invalid types in db_write/bool");
                }
                break;
        }

    }
    f.close();

}

template<typename T>
void Database::remove(T &piece) const {
    std::string dir;
    if (typeid(T) == typeid(Series)) {
        dir = SERIES_DIR;
    } else if (typeid(T) == typeid(Film)) {
        dir = FILMS_DIR;
    } else if (typeid(T) == typeid(Ppv)) {
        dir = PPVS_DIR;
    } else {
        throw std::runtime_error("Incorrect type passed to db_remove.");
    }
    fs::remove(dir + piece.getTitle());
}


#endif //SERIESTRACKER_DATABASE_HPP
