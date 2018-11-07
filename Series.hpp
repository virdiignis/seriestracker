//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_SERIES_HPP
#define SERIESTRACKER_SERIES_HPP

#define WEEKDAYS {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}

#include "constants.hpp"
#include <array>
#include "Film.hpp"

class Series : public Film {
private:
    unsigned short weekday;
    bool followed = false;
public:
    Series(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
           unsigned short weekday, const std::string &genre);

    const std::array<std::string, SERIES_LIST_PARAMS> getListParams() const;

    std::map<std::string, std::string> getDetails() const final;

    void switchFollow() noexcept;

    std::string strFollowed() const;

    bool isFollowed() const;

    std::string serialize() override;


};


#endif //SERIESTRACKER_SERIES_HPP
