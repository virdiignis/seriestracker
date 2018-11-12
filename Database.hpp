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

class Database {
private:
    void start();

    template<typename T>
    void load(Pool<T> &);

public:
    Database() = default;

    Database(Pool<Series> &, Pool<Film> &, Pool<Ppv> &);

    void write(Series *&);

    template<typename T>
    void write(T &);

    template<typename T>
    void remove(T &);

};


#endif //SERIESTRACKER_DATABASE_HPP
