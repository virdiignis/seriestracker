//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_PPV_HPP
#define SERIESTRACKER_PPV_HPP

#include "constants.hpp"
#include <array>
#include "Piece.hpp"
#include <ctime>

//! Represents Pay Per View/Live stream. Extends Piece with price, start time, and not yet implemented ability to remind about starting event.
class Ppv : public Piece {
private:
    float price = 0;
    time_t start_time = time(nullptr);
    bool reminder = false;

    //! Converts price to string, with 2 decimal places.
    std::string strPrice() const;

    //! Converts start_time to human-readable string.
    std::string strStartTime() const;

    friend class Interface;

    friend class Database;

    /*!
     * Allows access to class fields by pointer stored in std::variant, being indexed with human-readable fields names.
     * @param string: human-readable name of field, as provided in constants.hpp
     * @return std::variant with pointer to class field
     */
    std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](const std::string &) override;

    //! Sets ppv's price
    //! @param price: float
    void setPrice(float);

    //! Represents presence of reminder in human-readable form.
    std::string strReminder() const;

public:
    Ppv() = default;

    //! Changes presence of reminder
    void flipReminder() noexcept;

    /*!
     * Returns ppv's params needed to construct the listing.
     * @return map of (1) human-readable field name, (2) field value converted to h-r string
     */
    std::map<std::string, std::string> getListParams() const final;

    bool operator<(Ppv const &) const;

    /*!
     * Returns ppv's details.
     * @return map of (1) human-readable field name, (2) field value converted to h-r string
     */
    std::map<std::string, std::string> getDetails() const final;
};


#endif //SERIESTRACKER_PPV_HPP
