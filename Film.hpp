//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_FILM_HPP
#define SERIESTRACKER_FILM_HPP

#include "Piece.hpp"
#include <array>
#include <iomanip>
#include "constants.hpp"


class Film : public Piece {
protected:
    float grade = 0;
    std::string genre = "     ";

    std::string strGrade() const;

public:
    Film() = default;

    std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](std::string) override;

    std::map<std::string, std::string> getDetails() const override;

    std::string serialize() override;

    std::map<std::string, std::string> getListParams() const override;

    bool operator<(const Film &);
};


#endif //SERIESTRACKER_FILM_HPP
