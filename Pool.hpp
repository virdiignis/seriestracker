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
class Pool {
private:
    std::vector<T> pool;

public:
    explicit Pool(const std::vector<T> &);

    Pool() = default;

    const std::vector<T> getVec() const noexcept;

    void operator+=(T const &) noexcept;

    void operator-=(T const &);

    T &operator[](unsigned int index);

    Pool<T> sorted() const noexcept;

    std::string serialize() const noexcept;

};


#endif //SERIESTRACKER_POOL_HPP
