#include <iostream>
#include "Pool.cpp"


int main() {
    Pool<int> p;
    p += 1;
    std::cout << p.sorted()[0];
    return 0;
}