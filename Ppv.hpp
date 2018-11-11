//
// Created by prance on 22.10.18.
//

#ifndef SERIESTRACKER_PPV_HPP
#define SERIESTRACKER_PPV_HPP

#include "constants.hpp"
#include <array>
#include "Piece.hpp"
#include <ctime>

class Ppv : public Piece {
private:
    float price;
    time_t start_time;
    bool reminder = false;

    std::string strPrice() const;

    void setPrice(float price);

    std::string strStartTime() const;

    void setStartTime(time_t);

public:
    Ppv(const std::string &, const std::string &, unsigned short, float, time_t);

    std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](std::string) override;

    std::string strReminder() const;

    void flipReminder();

    std::map<std::string, std::string> getListParams() const override;

    std::string serialize() override;

    bool operator<(Ppv const &);

    std::map<std::string, std::string> getDetails() const override;
};


#endif //SERIESTRACKER_PPV_HPP
