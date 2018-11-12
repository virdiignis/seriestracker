//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_SERIES_HPP
#define SERIESTRACKER_SERIES_HPP

#include "constants.hpp"
#include <array>
#include "Film.hpp"

//! Represents Series, extends Film class.
class Series : public Film {
private:
    unsigned short weekday = 0;
    bool followed = false;

    friend class Interface;

    friend class Database;

    /*!
     * Allows access to class fields by pointer stored in std::variant, being indexed with human-readable fields names.
     * @param string: human-readable name of field, as provided in constants.hpp
     * @return std::variant with pointer to class field
     */
    std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](const std::string &) override;

public:
    Series() = default;

    //! Answers if series is followed by the user.
    const bool isFollowed() const;

    /*!
     * Returns series params needed to construct the listing.
     * @return map of (1) human-readable field name, (2) field value converted to h-r string
     */
    std::map<std::string, std::string> getListParams() const final;

    /*!
     * Returns series details.
     * @return map of (1) human-readable field name, (2) field value converted to h-r string
     */
    std::map<std::string, std::string> getDetails() const final;

    //! Follows/unfollows the series.
    void flipFollow() noexcept;

    //! Represents followed in human-readable form.
    std::string strFollowed() const;
};


#endif //SERIESTRACKER_SERIES_HPP
