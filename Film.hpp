//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_FILM_HPP
#define SERIESTRACKER_FILM_HPP

#include "constants.hpp"
#include "Piece.hpp"
#include <array>

class Film : public Piece {
protected:
    unsigned short grade;
    std::string genre;
public:
    Film(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
         const std::string &genre);

    std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](std::string) override;

    std::map<std::string, std::string> getDetails() const override;

    std::string strGrade() const;

    const std::string &getGenre() const;

    std::string serialize() override;

    std::map<std::string, std::string> getListParams() const override;

    bool operator<(const Film &);
};


#endif //SERIESTRACKER_FILM_HPP
