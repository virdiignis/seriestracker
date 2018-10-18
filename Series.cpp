//
// Created by prance on 17.10.18.
//

#include "Series.hpp"

Series::Series(const std::string &title, const std::string &desc, unsigned short runtime, unsigned short grade,
               unsigned short weekday, const std::string &genre, bool followed) : Piece(title, desc, runtime),
                                                                                  grade(grade),
                                                                                  weekday(weekday),
                                                                                  genre(genre),
                                                                                  followed(followed) {}
