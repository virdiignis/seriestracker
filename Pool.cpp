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
    else throw std::invalid_argument("Element not present in this!");
}

template<typename T>
void Pool<T>::sort() const noexcept {
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
