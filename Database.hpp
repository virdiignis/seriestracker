//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_DATABASE_HPP
#define SERIESTRACKER_DATABASE_HPP

#include <string>
#include <fstream>

class Database {
private:
    std::string filename;
    std::fstream filehandle;

public:
    explicit Database(const std::string &filename);

    void open();

    void close();

    void write(std::string const &);
};


#endif //SERIESTRACKER_DATABASE_HPP
