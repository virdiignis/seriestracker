//
// Created by prance on 17.10.18.
//

#include "Database.hpp"

Database::Database(const std::string &filename) : filename(filename) {}

void Database::open() {
    std::fstream filehandle(filename, std::fstream::in | std::fstream::out);
    if (!filehandle.good()) throw std::ifstream::failure("Opening file failed.\n");
}

void Database::close() {
    filehandle.close();
}

void Database::write(std::string const &data) {
    filehandle << data;
}
