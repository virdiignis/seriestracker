//
// Created by prance on 22.10.18.
//

#include <iomanip>
#include "Ppv.hpp"

Ppv::Ppv(const std::string &title, const std::string &desc, unsigned short runtime, float price, time_t startTime)
        : Piece(title, desc, runtime), price(price), start_time(startTime) {}

std::string Ppv::strReminder() const {
    return (reminder ? "[X]" : "[ ]");
}

void Ppv::flipReminder() {
    reminder = !reminder;
}

std::string Ppv::strPrice() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << price;
    return std::string(ss.str());
}

void Ppv::setPrice(float price) {
    Ppv::price = price;
}

std::string Ppv::strStartTime() const {
    char date[25];
    struct tm *dt;
    dt = localtime(&start_time);
    std::strftime(date, sizeof(date), "%d/%m/%Y %H:%M", dt);
    return std::string(date);
}

void Ppv::setStartTime(time_t start_time) {
    Ppv::start_time = start_time;
}

std::string Ppv::serialize() {
    return title + ":" + desc + ":" + std::to_string(runtime) + ":" + std::to_string(start_time) + ":" +
           std::to_string(price) + ":" + std::to_string(reminder);
}

std::map<std::string, std::string> Ppv::getListParams() const {
    auto m = Piece::getListParams();
    m["Price"] = strPrice();
    m["Start time"] = strStartTime();
    m["Reminder"] = strReminder();
    return m;
}

bool Ppv::operator<(Ppv const &oth) {
    return start_time < oth.start_time;
}

std::map<std::string, std::string> Ppv::getDetails() const {
    auto m = Piece::getDetails();
    m["Price"] = strPrice();
    m["Start time"] = strStartTime();
    m["Reminder"] = strReminder();
    return m;
}

std::variant<std::string *, unsigned short *, bool *, time_t *, float *> Ppv::operator[](std::string attr) {
    if (attr == "Price") return &price;
    if (attr == "Start time") return &start_time;
    if (attr == "Reminder") return &reminder;
    return Piece::operator[](attr);
}
