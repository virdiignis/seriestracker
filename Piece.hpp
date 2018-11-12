//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_PIECE_HPP
#define SERIESTRACKER_PIECE_HPP

#include <string>
#include <map>
#include <variant>

/*!
 * Virtual class representing a playable piece of art.
 */
class Piece {
protected:
    std::string title = "        ", desc = "        ";
    unsigned short runtime = 0;

    /*!
     * Allows access to class fields by pointer stored in std::variant, being indexed with human-readable fields names.
     * @param string: human-readable name of field, as provided in constants.hpp
     * @return std::variant with pointer to class field
     */
    virtual std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](const std::string &);

    Piece() = default;

public:
    /*!
     * Returns piece params needed to construct the listing.
     * @return map of (1) human-readable field name, (2) field value converted to h-r string
     */
    virtual std::map<std::string, std::string> getListParams() const;

    /*!
     * Returns piece details.
     * @return map of (1) human-readable field name, (2) field value converted to h-r string
     */
    virtual std::map<std::string, std::string> getDetails() const;

    bool operator==(const Piece &) const;

    //! Returns piece title.
    const std::string &getTitle() const;

};


#endif //SERIESTRACKER_PIECE_HPP
