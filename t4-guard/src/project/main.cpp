#include <iostream>
#include <fstream>

#include <random>
#include <algorithm>
#include "MyGuard.h"


void print_hex(int i) {
    MyGuard g(std::cout);
    std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
// или std::cout << std::hex
    std::cout << i << "\n";
}
int main(){

    print_hex(42);
    std::cout<<42;
    return 0;
}
