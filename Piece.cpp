//
// Created by prance on 17.10.18.
//

#include "Piece.hpp"

const std::string &Piece::getTitle() const {
    return title;
}

bool Piece::operator==(const Piece &oth) {
    return this->title == oth.title;
}

std::map<std::string, std::string> Piece::getDetails() const {
    std::map<std::string, std::string> m;
    m["Title"] = title;
    m["Description"] = desc;
    m["Runtime"] = std::to_string(runtime) + "min";
    return m;
}

std::map<std::string, std::string> Piece::getListParams() const {
    std::map<std::string, std::string> m;
    m["Title"] = title;
    return m;
}

std::variant<std::string *, unsigned short *, bool *, time_t *, float *> Piece::operator[](const std::string &attr) {
    if (attr == "Title") return &title;
    if (attr == "Description") return &desc;
    if (attr == "Runtime") return &runtime;
    throw std::runtime_error("required non-existing Piece attribute");
}
