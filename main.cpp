#include <iostream>
#include "Series.hpp"
#include "Interface.hpp"
#include "Pool.cpp"


int main() {
    Pool<Series> p;
    //std::cout << p.sorted()[0];
    p += Series("Dexter", "Very interesting series about killing.", 43, 89, 7, "Drama");
    Interface a;
    a.list(p);
    a.menu();
    return 0;
}