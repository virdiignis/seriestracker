//
// Created by prance on 15.10.18.
//

#include "Pool.hpp"


template<typename T>
void Pool<T>::operator+=(T const &element) noexcept {
    this->push_back(element);
}

template<typename T>
void Pool<T>::operator-=(T const &element) {
    auto it = std::find(this->begin(), this->end(), element);
    if (it != this->end()) this->erase(it);
    else throw std::invalid_argument("Element not present in pool!");
}

template<typename T>
void Pool<T>::sort() noexcept {
    //auto p = this;  //copy
    //std::copy(this.begin(), this.end(), std::back_inserter(series_pool));
    std::sort(this->begin(), this->end());
    //return p;
}

template<typename T>
std::string Pool<T>::serialize() const noexcept {
    std::string r;
    for (auto &it: *this) r += it.serialize() += "\n";
    return r;
}

template<typename T>
void Pool<T>::operator-=(int i) {
    if (this->size() <= i) throw std::invalid_argument("Index out of range!");
    this->erase(this->begin() + i);
}

template<typename T>
Pool<Series> Pool<T>::filtered() const {
    if (typeid(T) != typeid(Series)) throw std::domain_error("Only pool of type Series can be filtered.");
    Pool<Series> p;
    for (auto &item: *this) if (item.isFollowed()) p += item;
    return p;
}


