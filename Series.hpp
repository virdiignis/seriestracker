//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_SERIES_HPP
#define SERIESTRACKER_SERIES_HPP


#include "Piece.hpp"

class Series : public Piece {
private:
    unsigned short grade, weekday;
    std::string genre;
    bool followed = false;

public:
    Series(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
           unsigned short weekday, const std::string &genre, bool followed);
};


#endif //SERIESTRACKER_SERIES_HPP
