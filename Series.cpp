//
// Created by prance on 17.10.18.
//

#include "Series.hpp"

void Series::flipFollow() noexcept {
    followed = !followed;
}

std::map<std::string, std::string> Series::getListParams() const {
    auto m = Film::getListParams();
    m["Followed"] = strFollowed();
    return m;
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

const bool Series::isFollowed() const {
    return followed;
}

std::variant<std::string *, unsigned short *, bool *, time_t *, float *> Series::operator[](const std::string &attr) {
    if (attr == "Followed") return &followed;
    if (attr == "Weekday") return &weekday;
    return Film::operator[](attr);
}
