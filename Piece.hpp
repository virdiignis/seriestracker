//
// Created by prance on 17.10.18.
//

#ifndef SERIESTRACKER_PIECE_HPP
#define SERIESTRACKER_PIECE_HPP

#include <string>

class Piece {
private:
    std::string title, desc;
    unsigned short runtime;

protected:
    Piece(const std::string &title, const std::string &desc, unsigned short runtime);

public:
    const std::string &getTitle() const;

    const std::string &getDesc() const;

    unsigned short getRuntime() const;

    virtual std::string serialize() = 0;

};


#endif //SERIESTRACKER_PIECE_HPP
