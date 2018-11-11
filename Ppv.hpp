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
    float price = 0;
    time_t start_time = time(nullptr);
    bool reminder = false;

    friend class Interface;

    std::string strPrice() const;

    std::string strStartTime() const;

    std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](std::string) override;

    void setPrice(float price);

public:
    Ppv() = default;

    std::string strReminder() const;

    void flipReminder();

    std::map<std::string, std::string> getListParams() const override;

    std::string serialize() override;

    bool operator<(Ppv const &);

    std::map<std::string, std::string> getDetails() const override;
};


#endif //SERIESTRACKER_PPV_HPP
