//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_PIECE_HPP
#define SERIESTRACKER_PIECE_HPP

#include <string>
#include <map>
#include <variant>

class Piece {
protected:
    std::string title = "     ", desc = "     ";
    unsigned short runtime = 0;

    virtual std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](const std::string &);

    Piece() = default;

public:
    virtual std::map<std::string, std::string> getListParams() const;

    virtual std::map<std::string, std::string> getDetails() const;

    bool operator==(const Piece &);

    const std::string &getTitle() const;

    virtual std::string serialize() = 0;

};


#endif //SERIESTRACKER_PIECE_HPP
