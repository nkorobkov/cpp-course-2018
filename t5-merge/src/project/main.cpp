#include <iostream>
#include <fstream>

#include <random>
#include <algorithm>


template <typename T>
void merge(T xf, T xl, T yf, T yl){
    T f = xf;

    unsigned long const size = yl-xf;
    std::vector<typename T::value_type> buf;
    int i = 0;
    while (i< size){
        if(xf == xl){
            buf.insert(buf.begin()+i, yf,yl);
            break;
        }
        if(yf == yl){
            buf.insert(buf.begin()+i, xf,xl);
            break;
        }
        if(*xf >= *yf){
            buf.push_back(*xf);
            xf++;
        }else{
            buf.push_back(*yf);
            yf++;
        }
        i++;
    }
    std::copy(buf.begin(), buf.end(), f);

}

template <typename T>
void m_sort(T first, T last){
    long size = std::distance(first,last);
    if (size < 2)
        return;
    T middle = std::next(first, size / 2);
    m_sort(first, middle);
    m_sort(middle, last);
    merge(first, middle,middle, last);
}


int main() {
    std::vector<int> acc = {1,2,3,4,5,6,7,8,9};

    m_sort(acc.begin(), acc.end());

    for(int i : acc){
        std::cout << i <<" ";
    }
    return 0;
}
