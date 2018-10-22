//
// Created by prance on 17.10.18.
//

#include "Series.hpp"

Series::Series(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
               unsigned short weekday, const std::string &genre) : Film(title, desc, runtime, grade, genre),
                                                                   weekday(weekday) {}

bool Series::isFollowed() const noexcept {
    return followed;
}

void Series::follow() noexcept {
    followed = true;
}

void Series::unfollow() noexcept {
    followed = false;
}

unsigned short Series::getWeekday() const {
    return weekday;
}

std::string Series::serialize() {
    return title + ":" + desc + ":" + std::to_string(runtime) + ":" + std::to_string(grade) + ":" +
           std::to_string(weekday) + ":" + genre + ":" + std::to_string(followed);
}
