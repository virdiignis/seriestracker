//
// Created by prance on 15.10.18.
//

#include "Pool.hpp"


template<typename T>
void Pool<T>::operator+=(T element) noexcept {
    pool.push_back(element);
}

template<typename T>
void Pool<T>::operator-=(T element) {
    auto it = std::find(pool.begin(), pool.end(), element);
    if (it != pool.end()) pool.erase(it);
    else throw std::invalid_argument("Element not present in pool!");
}

template<typename T>
Pool<T>::Pool(std::vector<T> v) {
    pool = v;
}

template<typename T>
const std::vector<T> Pool<T>::getVec() const noexcept {
    return pool;
}

template<typename T>
T &Pool<T>::operator[](unsigned int index) {
    return pool[index];
}

template<typename T>
Pool<T> Pool<T>::sorted() const noexcept {
    std::vector<T> p;
    std::copy(pool.begin(), pool.end(), std::back_inserter(p));
    std::sort(p.begin(), p.end());
    return Pool<T>(p);
}

template<typename T>
std::string Pool<T>::serialize() const noexcept {
    std::string r;
    for (auto &it: pool) r += it->serialize() += "\n";
    return r;
}
