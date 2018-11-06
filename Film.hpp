//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_FILM_HPP
#define SERIESTRACKER_FILM_HPP
#define FILM_LIST_PARAMS 3

#include "Piece.hpp"
#include <array>

class Film : public Piece {
protected:
    unsigned short grade;
    std::string genre;
public:
    Film(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
         const std::string &genre);

    unsigned short getGrade() const;

    const std::string &getGenre() const;

    std::string serialize() override;

    virtual const std::array<std::string, FILM_LIST_PARAMS> getListParams() const;

    bool operator<(const Film &);
};


#endif //SERIESTRACKER_FILM_HPP
