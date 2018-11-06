//
// Created by prance on 17.10.18.
//

#include "Series.hpp"

Series::Series(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
               unsigned short weekday, const std::string &genre) : Film(title, desc, runtime, grade, genre),
                                                                   weekday(weekday) {}

void Series::sfollow() noexcept {
    followed = !followed;
}

std::string Series::serialize() {
    return title + ":" + desc + ":" + std::to_string(runtime) + ":" + std::to_string(grade) + ":" +
           std::to_string(weekday) + ":" + genre + ":" + std::to_string(followed);
}

const std::array<std::string, SERIES_LIST_PARAMS> Series::getListParams() const {
    std::array<std::string, SERIES_LIST_PARAMS> r = {title,
                                                     genre,
                                                     std::to_string(grade / 10) + "," + std::to_string(grade % 10),
                                                     (followed ? "[X]" : "[ ]")};
    return r;
}

bool Series::isFollowed() const {
    return followed;
}
