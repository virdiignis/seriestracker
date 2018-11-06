//
// Created by prance on 15.10.18.
//

#ifndef SERIESTRACKER_POOL_HPP
#define SERIESTRACKER_POOL_HPP


#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Pool : public std::vector<T> {
public:
    void operator+=(T const &) noexcept;

    void operator-=(T const &);

    void sort() const noexcept;

    std::string serialize() const noexcept;

};


#endif //SERIESTRACKER_POOL_HPP
