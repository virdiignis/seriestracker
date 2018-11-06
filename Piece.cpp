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

unsigned short Piece::getRuntime() const {
    return runtime;
}

Piece::Piece(const std::string &title, const std::string &desc, unsigned short runtime) : title(title), desc(desc),
                                                                                          runtime(runtime) {}

void Piece::setDesc(const std::string &desc) {
    Piece::desc = desc;
}

bool Piece::operator==(const Piece &oth) {
    return this->title == oth.title;
}
