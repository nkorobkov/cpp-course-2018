#include <iostream>

#include <fstream>
#include <random>
#include <algorithm>
#include <future>
#include <thread>
#include <myproject/t8-thread/TaskPool.cpp>
#include <random>

std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> dis(1, 10000);

void test_on_size(int n){
    std::vector<int> acc1;
    std::vector<int> acc2;
    std::vector<int> acc3;
    std::chrono::milliseconds sec(1);
    int v;
    for (int i = 1; i < n; i++) {
        v = dis(gen);
        acc1.push_back(v);
        acc2.push_back(v);
        acc3.push_back(v);
    }
    auto SM = new SortingMachine<std::vector<int>::iterator>(acc2.begin(), acc2.end());
    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    SM->start();
    SM->sort();
    auto async = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t).count();
    t = std::chrono::system_clock::now();
    m_sort(acc1.begin(), acc1.end());
    auto reg = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t).count();
    int i=0;
    for(;i<acc1.size();i++){
        if(acc1[i] != acc2[i]){
            std::cout<<"WA"<<std::to_string(i);
            break;
        }
    }
    bool correct  = i == acc1.size();
    std::cout<< "size=";
    std::cout.width(9);
    std::cout<< n ;
    std::cout<< " reg = ";
    std::cout.width(10);
    std::cout<< reg;
    std::cout<< " async = ";
    std::cout.width(10);
    std::cout<< async;
    std::cout<<" Correctness = ";
    std::cout<< std::to_string(correct) <<"\n";
}

int main() {
    std::cout.fill(' ');
    std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 500000};
    for (int s : sizes){
        test_on_size(s);
    }
    return 0;
}

/*
 *
size=       10 reg =         49 async =       3636 Correctness = 1
size=      100 reg =        159 async =        417 Correctness = 1
size=     1000 reg =       2422 async =       2830 Correctness = 1
size=    10000 reg =      24931 async =      21269 Correctness = 1
size=   100000 reg =     448361 async =     328648 Correctness = 1
size=   500000 reg =    2437480 async =    1898943 Correctness = 1
 */