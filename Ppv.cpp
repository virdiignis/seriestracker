//
// Created by prance on 22.10.18.
//

#include "Ppv.hpp"

Ppv::Ppv(const std::string &title, const std::string &desc, unsigned short runtime, float price, time_t start_time)
        : Piece(title, desc, runtime), price(price), start_time(start_time) {}

bool Ppv::isReminder() const {
    return reminder;
}

void Ppv::setReminder(bool reminder) {
    Ppv::reminder = reminder;
}

float Ppv::getPrice() const {
    return price;
}

void Ppv::setPrice(float price) {
    Ppv::price = price;
}

time_t Ppv::getStart_time() const {
    return start_time;
}

void Ppv::setStart_time(time_t start_time) {
    Ppv::start_time = start_time;
}

std::string Ppv::serialize() {
    return title + ":" + desc + ":" + std::to_string(runtime) + ":" + std::to_string(start_time) + ":" +
           std::to_string(price);
}
