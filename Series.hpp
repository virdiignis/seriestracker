//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_SERIES_HPP
#define SERIESTRACKER_SERIES_HPP


#include "Film.hpp"

class Series : public Film {
private:
    unsigned short weekday;
    bool followed = false;
public:
    unsigned short getWeekday() const;

    bool isFollowed() const noexcept;

    void follow() noexcept;

    void unfollow() noexcept;

    std::string serialize() override;

    Series(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
           unsigned short weekday, const std::string &genre);
};


#endif //SERIESTRACKER_SERIES_HPP
