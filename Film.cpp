//
// Created by prance on 22.10.18.
//

#include "Film.hpp"

std::string Film::strGrade() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << grade;
    return std::string(ss.str());
}

std::string Film::serialize() {
    return title + ":" + desc + ":" + std::to_string(runtime) + ":" + std::to_string(grade) + ":" + genre;
}

bool Film::operator<(const Film &rhs) {
    return grade > rhs.grade;
}

std::map<std::string, std::string> Film::getListParams() const {
    auto m = Piece::getListParams();
    m["Genre"] = genre;
    m["Grade"] = strGrade();
    return m;
}

std::map<std::string, std::string> Film::getDetails() const {
    auto m = Piece::getDetails();
    m["Genre"] = genre;
    m["Grade"] = strGrade();
    return m;
}

std::variant<std::string *, unsigned short *, bool *, time_t *, float *> Film::operator[](const std::string attr) {
    if (attr == "Genre") return &genre;
    if (attr == "Grade") return &grade;
    return Piece::operator[](attr);
}
