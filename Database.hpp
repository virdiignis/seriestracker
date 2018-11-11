//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_DATABASE_HPP
#define SERIESTRACKER_DATABASE_HPP

#define BASE_DIR ".seriestracker"

#define SERIES_DIR ".seriestracker/series"

#define FILMS_DIR ".seriestracker/films"

#define PPVS_DIR ".seriestracker/ppvs"

#include <string>
#include <fstream>
#include <filesystem>
#include "Series.hpp"
#include "Pool.hpp"
#include "Ppv.hpp"

namespace fs = std::filesystem;

class Database {
private:
    void start();

    void load(Pool<Series> &);

    void load(Pool<Film> &);

    void load(Pool<Ppv> &);

public:
    explicit Database(const std::string &filename);

    void close();

    void write(std::string const &);
};


#endif //SERIESTRACKER_DATABASE_HPP
