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

    std::string strPrice() const;

    std::string strStartTime() const;

    friend class Interface;

    friend class Database;

    std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](std::string) override;

    void setPrice(float price);

    std::string strReminder() const;

public:
    Ppv() = default;

    void flipReminder();

    std::map<std::string, std::string> getListParams() const final;

    std::string serialize() override;

    bool operator<(Ppv const &);

    std::map<std::string, std::string> getDetails() const final;
};


#endif //SERIESTRACKER_PPV_HPP
