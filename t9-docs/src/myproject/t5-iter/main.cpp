#include <iostream>
#include <fstream>

#include <random>
#include <algorithm>
#include "MyIterator.h"


int main(){
    MyIterator<int> itr(std::cout, 3);
    std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    std::copy(vec.begin(), vec.end(), itr);
    return 0;
}
