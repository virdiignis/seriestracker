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
    std::string title, desc;
    unsigned short runtime;

protected:
    Piece(const std::string &title, const std::string &desc, unsigned short runtime);

public:
    virtual std::variant<std::string *, unsigned short *, bool *, time_t *, float *> operator[](std::string);

    virtual std::map<std::string, std::string> getListParams() const;

    virtual std::map<std::string, std::string> getDetails() const;

    bool operator==(const Piece &);

    const std::string &getTitle() const;

    const std::string &getDesc() const;

    void setDesc(const std::string &desc);

    unsigned short getRuntime() const;

    virtual std::string serialize() = 0;

};


#endif //SERIESTRACKER_PIECE_HPP
