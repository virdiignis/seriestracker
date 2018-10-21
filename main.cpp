#include <iostream>
#include "Pool.cpp"
#include "Series.hpp"


int main() {
    Pool<Piece *> p;
    p += new Series("Dexter", "Ziom zabija chujów", 40, 88, 6, "drama");
    std::cout << p[0]->serialize();
    return 0;
}