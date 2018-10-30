#include <iostream>

#include <fstream>
#include <random>
#include <algorithm>
#include <future>
#include <thread>
#include "TaskPool.cpp"



template<typename T>
void merge(T xf, T xl, T yf, T yl) {
    T f = xf;

    unsigned long const size = yl - xf;
    std::vector<typename T::value_type> buf;
    int i = 0;
    while (i < size) {
        if (xf == xl) {
            buf.insert(buf.begin() + i, yf, yl);
            break;
        }
        if (yf == yl) {
            buf.insert(buf.begin() + i, xf, xl);
            break;
        }
        if (*xf >= *yf) {
            buf.push_back(*xf);
            xf++;
        } else {
            buf.push_back(*yf);
            yf++;
        }
        i++;
    }
    std::copy(buf.begin(), buf.end(), f);

}

template<typename T>
void m_sort(T first, T last) {
    long size = std::distance(first, last);
    if (size < 2)
        return;
    T middle = std::next(first, size / 2);
    m_sort(first, middle);
    m_sort(middle, last);
    merge(first, middle, middle, last);
}




int main() {
    std::vector<int> acc1;
    std::vector<int> acc2;
    std::vector<int> acc3;

    std::chrono::milliseconds sec(1);

    for (int i = 1; i < 10; i++) {
        acc1.push_back(i);
        acc2.push_back(i);
        acc3.push_back(i);
    }
    auto SM = new SortingMachine<std::vector<int>::iterator>(acc2.begin(), acc2.end());

    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    SM->start();
    SM->sort();

    //SM->stop();
    //SM->wait();

    auto async = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t).count();


    t = std::chrono::system_clock::now();


    m_sort(acc1.begin(), acc1.end());

    auto reg = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t).count();

    std::cout << "reg = " << reg << " async = " << async<<"\n";
    int i=0;
//    for(;i<acc1.size();i++){
//        if(acc1[i] != acc2[i]){
//            std::cout<<"WA"<<std::to_string(i);
//            break;
//        }
//    }

    for(;i<10;i++){

        std::cout<<std::to_string(acc1[i]) <<"   "<<std::to_string(acc2[i])<<"\n";

    }
    if(i == acc1.size()){
        std::cout<<"Sorting correct";
    }
    return 0;
}