//
// Created by prance on 17.10.18.
//

#include "Piece.hpp"

const std::string &Piece::getTitle() const {
    return title;
}

const std::string &Piece::getDesc() const {
    return desc;
}

unsigned short int Piece::getRuntime() const {
    return runtime;
}
