#include <iostream>

#include "MyVector.cc"
#include <fstream>
#include <random>
#include <algorithm>

int main(void){


    std::random_device rd;

    MyVector<std::ofstream> vecs;
    vecs.push_back(std::ofstream ("a"));
    vecs.push_back(std::ofstream ("b"));
    vecs.push_back(std::ofstream ("c"));
    std::cout  << vecs.size();

    std::shuffle(vecs.begin(), vecs.end(), rd);

    MyVector<std::ofstream> vecs2;
    vecs2 = vecs;

    *(vecs2.begin()) << 1;
    *(vecs2.begin()+1) << 2;
    *(vecs2.begin()+2) << 3;

    return 0;
}