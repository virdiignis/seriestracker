#include <iostream>
#include "Pool.cpp"
#include "Series.hpp"
#include "Interface.hpp"


int main() {
    Pool<int> p;
    p += 3;
    p += 2;
    p += 1;
    p -= 2;
    //std::cout << p.sorted()[0];
    //Series a("","",0,0,0,"");
    Interface a;
    a.menu();
    return 0;
}