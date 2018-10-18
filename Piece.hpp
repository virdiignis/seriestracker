//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_PIECE_HPP
#define SERIESTRACKER_PIECE_HPP

#include <string>

class Piece {
private:
    std::string title, desc;
    unsigned short int runtime;

public:
    const std::string &getTitle() const;

    const std::string &getDesc() const;

    unsigned short int getRuntime() const;

    virtual std::string serialize() = 0;

};


#endif //SERIESTRACKER_PIECE_HPP
