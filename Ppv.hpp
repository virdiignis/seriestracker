//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_PPV_HPP
#define SERIESTRACKER_PPV_HPP


#include "Piece.hpp"

class Ppv : public Piece {
private:
    float price;
    time_t start_time;
    bool reminder = false;

public:
    Ppv(const std::string &title, const std::string &desc, unsigned short runtime, float price, time_t start_time);

    float getPrice() const;

    void setPrice(float price);

    time_t getStart_time() const;

    void setStart_time(time_t start_time);

    bool isReminder() const;

    void setReminder(bool reminder);

    std::string serialize() override;
};


#endif //SERIESTRACKER_PPV_HPP
