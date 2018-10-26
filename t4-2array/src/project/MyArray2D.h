//#include "MyMaskedArray2D.h"
#include <fstream>

#include <random>
#include <algorithm>


template<typename D>
class MyMaskedArray2D;

template<class T>
class MyArray2D {

public:
    template<typename D>
    friend
    class MyMaskedArray2D;

    int w;
    int h;
    T *values;

    MyArray2D<T>() {
        MyArray2D(1, 1);
    }

    MyArray2D<T>(int h, int w) : w(w), h(h) {
        values = new T[h * w];
    }

    MyArray2D<T>(int h, int w, T *_values) : w(w), h(h) {
        values = new T[h * w];
        std::copy(_values, _values + w * h, values);
    }

    MyArray2D<T>(MyArray2D &other) : w(other.w), h(other.h) {
        values = new T[h * w];
        for (int i = 0; i < h * w; i++) {
            this->values[i] = (other.values[i]);
        }
        //std::copy(other.values, other.values+w*h, values);
    }

    ~MyArray2D() {
        delete[] values;
        h = 0;
        w = 0;
    }

    T operator()(int i, int j) { //zero indexing
        return *(values + (i * w) + j);
    }


    MyArray2D<T> operator=(const MyArray2D &other) {
        std::copy(other.values, other.values + w * h, values);
        return *this;

    }

    MyArray2D<T> operator+(MyArray2D other) {
        MyArray2D<T> result(other);
        for (int i = 0; i < h * w; i++) {
            result.values[i] += (values[i]);
        }
        return result;

    };

    void setValues(int *vals) {
        std::copy(vals, vals + h * w, values);
    }

    MyArray2D<T> operator-(MyArray2D other) {
        MyArray2D<T> result(*this);
        for (int i = 0; i < h * w; i++) {
            result.values[i] -= (other.values[i]);
        }
        return result;
    };

    MyArray2D<T> operator*(MyArray2D other) {
        MyArray2D<T> result(other);
        for (int i = 0; i < h * w; i++) {
            result.values[i] *= (values[i]);
        }
        return result;
    };

//    MyArray2D<T> operator/(MyArray2D other) {
//        MyArray2D<T> result(*this);
//        for (int i = 0; i < h * w; i++) {
//            result.values[i] /= (other.values[i]);
//        }
//        return result;
//    };

    MyArray2D<bool> operator<(const MyArray2D other) {
        MyArray2D<bool> result(other.h, other.w);

        for (int i = 0; i < h * w; i++) {
            result.values[i] = other.values[i] > (values[i]);
        }
        return result;
    };

    MyArray2D<bool> operator>(const MyArray2D other) {
        MyArray2D<bool> result(other.h, other.w);

        for (int i = 0; i < h * w; i++) {
            result.values[i] = other.values[i] < (values[i]);
        }
        return result;
    };

    MyArray2D<bool> operator==(const MyArray2D other) {
        MyArray2D<bool> result(other.h, other.w);

        for (int i = 0; i < h * w; i++) {
            result.values[i] = other.values[i] == (values[i]);
        }
        return result;
    };


    MyMaskedArray2D<T> operator()(const MyArray2D<bool> &mask) {
        return MyMaskedArray2D<T>(*this, mask);
    };
};

