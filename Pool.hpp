//
// Created by prance on 15.10.18.
//

#ifndef SERIESTRACKER_POOL_HPP
#define SERIESTRACKER_POOL_HPP


#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "Series.hpp"

/*!
 * Pool of objects, extends std::vector with overloaded operators, sorting method and filtering by parameter.
 * @tparam T: type of contained objects
 */
template<typename T>
class Pool : public std::vector<T> {
public:
    void operator+=(T const &) noexcept;

    void operator-=(T const &);

    void operator-=(int);

    //! Sorting the pool with standard operator< of contained objects.
    void sort() noexcept;

    Pool<Series *> filtered();
};


#endif //SERIESTRACKER_POOL_HPP
