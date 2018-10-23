//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_SERIES_HPP
#define SERIESTRACKER_SERIES_HPP
#define SERIES_LIST_PARAMS 4

#include <array>
#include "Film.hpp"

class Series : public Film {
private:
    unsigned short weekday;
    bool followed = false;
public:
    Series(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
           unsigned short weekday, const std::string &genre);

    unsigned short getWeekday() const;

    const std::array<std::string, SERIES_LIST_PARAMS> getListParams() const;

    bool isFollowed() const noexcept;

    void follow() noexcept;

    void unfollow() noexcept;

    std::string serialize() override;


};


#endif //SERIESTRACKER_SERIES_HPP
