//
// Created by prance on 22.10.18.
//

#include "Film.hpp"

Film::Film(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
           const std::string &genre) : Piece(title, desc, runtime),
                                       grade(grade),
                                       genre(genre) {}

std::string Film::getGrade() const {
    return std::to_string(grade / 10) + "," + std::to_string(grade % 10);
}

const std::string &Film::getGenre() const {
    return genre;
}

std::string Film::serialize() {
    return title + ":" + desc + ":" + std::to_string(runtime) + ":" + std::to_string(grade) + ":" + genre;
}

bool Film::operator<(const Film &rhs) {
    return grade > rhs.grade;
}

const std::array<std::string, FILM_LIST_PARAMS> Film::getListParams() const {
    std::array<std::string, FILM_LIST_PARAMS> r = {title,
                                                   genre,
                                                   getGrade()};
    return r;
}

std::map<std::string, std::string> Film::getDetails() const {
    auto m = Piece::getDetails();
    m["Genre"] = genre;
    m["Grade"] = getGrade();
    return m;
}
