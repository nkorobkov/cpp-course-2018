#include <iostream>
#include <fstream>

#include <random>
#include <algorithm>
#include "MyMaskedArray2D.h"


int main() {
    MyArray2D<int> a(2, 3);
    int av[] = {-2, -1, 0, 1,  2,  3};
    int cv[] = { 3,  2, 1, 0, -1, -100};
    a.setValues(av);

    MyArray2D<int> c(2, 3);

    c.setValues(cv);

    MyArray2D<bool> res(2, 3);
    res = c<a;

    bool v[] = {true, true, true, true, false, true};

    MyArray2D<bool> m(2,3, v);

    //res(m) = 3;

    for (int i = 0; i < a.h; i++) {
        for (int j = 0; j < a.w; j++) {
            int f = a(i, j);
            std::cout << f<<" ";
        }
        std::cout<<"\n";
    }
    return 0;
}
