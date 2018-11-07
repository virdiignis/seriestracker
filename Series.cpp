//
// Created by prance on 17.10.18.
//

#include "Series.hpp"

Series::Series(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
               unsigned short weekday, const std::string &genre) : Film(title, desc, runtime, grade, genre),
                                                                   weekday(weekday) {}

void Series::switchFollow() noexcept {
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
                                                     strFollowed()};
    return r;
}

std::string Series::strFollowed() const {
    return followed ? "[X]" : "[ ]";
}

std::map<std::string, std::string> Series::getDetails() const {
    auto m = Film::getDetails();
    m["Followed"] = strFollowed();
    const std::string weekdays[] = WEEKDAYS;
    try {
        m["Weekday"] = weekdays[weekday];
    } catch (std::bad_alloc &e) {
        throw std::out_of_range("Series " + title + " has weekday that doesn't exist.");
        //"Somehow we've got weekday other than the seven we know of.
        // That's really kinda bad, so I'm just going to throw that exception,
        // because I can't thing of how much I'd need to screw this code for this to happen...

    }
    return m;
}

bool Series::isFollowed() const {
    return followed;
}
