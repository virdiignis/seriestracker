//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_SERIES_HPP
#define SERIESTRACKER_SERIES_HPP


#include "Piece.hpp"

class Series : public Piece {
private:
    unsigned short grade, weekday;
    std::string genre;
    bool followed = false;
public:
    unsigned short getGrade() const;

    unsigned short getWeekday() const;

    const std::string &getGenre() const;

    bool isFollowed() const noexcept;

    void follow() noexcept;

    void unfollow() noexcept;

    std::string serialize() override;

public:
    Series(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
           unsigned short weekday, const std::string &genre);
};


#endif //SERIESTRACKER_SERIES_HPP
