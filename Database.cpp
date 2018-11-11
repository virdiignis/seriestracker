//
// Created by prance on 17.10.18.
//

#include "Database.hpp"

void Database::start() {
    try {
        if (!fs::exists(BASE_DIR)) fs::create_directory(BASE_DIR);
        if (!fs::exists(SERIES_DIR)) fs::create_directory(SERIES_DIR);
        if (!fs::exists(FILMS_DIR)) fs::create_directory(FILMS_DIR);
        if (!fs::exists(PPVS_DIR)) fs::create_directory(PPVS_DIR);
    } catch (fs::filesystem_error &e) {
        throw std::runtime_error("Cannot create db directories!");
    }
}

void Database::load(Pool<Series> &pool) {
    for (auto &it: fs::directory_iterator(SERIES_DIR)) {
        Series n;
        std::ifstream f(stdit);
    }
}

void Database::load(Pool<Film> &pool) {

}

void Database::load(Pool<Ppv> &pool) {

}
