#include <iostream>
#include <fstream>

#include <random>
#include <algorithm>
#include "Pair.h"


int main() {
    Pair p = Pair(4, 5);
    Pair pp = rotate(p, 3);
    std::cout<<pp.x<<" "<<pp.y<<"\n";
    return 0;
}
