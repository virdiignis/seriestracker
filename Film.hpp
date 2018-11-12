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

    /*!
     * Converts float-represented grade to std::string with one decimal place
     * @return std::string represented grade
     */
    std::string strGrade() const;

    friend class Interface;

    friend class Database;

    /*!
     * Allows access to class fields by pointer stored in std::variant, being indexed with human-readable fields names.
     * @param string: human-readable name of field, as provided in constants.hpp
     * @return std::variant with pointer to class field
     */
    std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](const std::string &) override;

public:
    Film() = default;

    /*!
     * Returns film details.
     * @return map of (1) human-readable field name, (2) field value converted to h-r string
     */
    std::map<std::string, std::string> getDetails() const override;

    /*!
     * Returns film params needed to construct the listing.
     * @return map of (1) human-readable field name, (2) field value converted to h-r string
     */
    std::map<std::string, std::string> getListParams() const override;

    bool operator<(const Film &) const;
};


#endif //SERIESTRACKER_FILM_HPP
