//
// Created by prance on 22.10.18.
//

#include "Film.hpp"

Film::Film(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
           const std::string &genre) : Piece(title, desc, runtime),
                                       grade(grade),
                                       genre(genre) {}

unsigned short Film::getGrade() const {
    return grade;
}

const std::string &Film::getGenre() const {
    return genre;
}

std::string Film::serialize() {
    return title + ":" + desc + ":" + std::to_string(runtime) + ":" + std::to_string(grade) + ":" + genre;
}
