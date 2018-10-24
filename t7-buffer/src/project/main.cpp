#include <iostream>
#include <fstream>

#include <random>
#include <algorithm>

#include "LineNumberBuffer.cpp"



int main() {
    std::ofstream out{"out.txt"};
    std::streambuf* oldbuf = std::cout.rdbuf();
    LineNumberBuffer lineNumberBuffer {oldbuf};
    std::cout.rdbuf(&lineNumberBuffer);
    //char a[256];


//   while(std::cin){
//       std::cin.get(a,256);
//       std::cout << a;
//   }
    std::cout << std::cin.rdbuf();

    std::cout.rdbuf(oldbuf); // восстанавливаем старый буфер
}
