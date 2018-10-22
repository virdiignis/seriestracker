//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_FILM_HPP
#define SERIESTRACKER_FILM_HPP


#include "Piece.hpp"

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
};


#endif //SERIESTRACKER_FILM_HPP
