//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_SERIES_HPP
#define SERIESTRACKER_SERIES_HPP

#include "constants.hpp"
#include <array>
#include "Film.hpp"

class Series : public Film {
private:
    unsigned short weekday = 0;
    bool followed = false;

    friend class Interface;

    friend class Database;

    std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](const std::string &) override;

public:
    Series() = default;

    const bool isFollowed() const;

    std::map<std::string, std::string> getListParams() const final;

    std::map<std::string, std::string> getDetails() const final;

    void flipFollow() noexcept;

    std::string strFollowed() const;
};


#endif //SERIESTRACKER_SERIES_HPP
