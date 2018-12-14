
#include <algorithm>
#include <iterator>

template<class T>
class MyVector {

public:

    MyVector(const MyVector &other) {
        vals = new T[other._capacity];
        std::copy(other.vals, other.vals + other.size(), vals);
        _size = other.size();
        _capacity = other._capacity;
    }

    MyVector(MyVector &&other) {
        vals = std::move(other.vals);
        _size = other._size;
        _capacity = other._capacity;
        other._size = 0;
        other._capacity = 0;
        other.vals = nullptr;

    }

    MyVector() {
        _capacity = 1;
        _size = 0;
        vals = new T[_capacity];
    }

    ~MyVector(){
        delete[] vals;
    }

    MyVector<T> &operator=(const MyVector &other) {
        delete[] this->vals ;
        vals = new T[other._capacity];
        for(int i = 0; i<other.size();i++){
            vals[i] = std::move(other.vals[i]);
        }
        _size = other.size();
        _capacity = other._capacity;
        return *this;
    }

    MyVector<T> &operator=(MyVector &&other) {
        vals = std::move(other.vals);
        _size = other._size;
        _capacity = other._capacity;
        other._capacity = 0;
        other._size = 0;
        other.vals = nullptr;
        return *this;
    }

    void swap(MyVector &other) {
        std::swap(vals, other.vals);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    T *begin() {
        return vals;
    };

    T *end() {
        return vals + _size;
    };

    int size() const {
        return _size;
    };

    void erase(T *pos) {
        for (int i = 0; pos + i+1 != vals + _size; ++i) {
            pos + i = std::move(pos+i+1);
        }
        _size--;
    }

    void erase(T *first, T *last) {
        for (int i = 0; last + i+1 != vals + _size; ++i) {
            first + i = std::move(last+i+1);
        }
        _size -= last - first;
    }

    void push_back(T &v) {
        if (_size == _capacity) {
            T *newVals = new T[_size * 2];
            _capacity = _size * 2;
            std::copy(this->begin(), this->end(), newVals);
            delete [] vals;
            vals = newVals;

        }
        vals[_size] = v; // *(vals+_size) = v
        _size++;
    }


    void push_back(T &&v) {
        if (_size == _capacity) {
            T *newVals = new T[_size * 2];
            _capacity = _size * 2;
            for (int i = 0; i < _size; i++) {
                newVals[i] = std::move(vals[i]);
            }
            delete[] vals;
            vals = newVals;
        }
        vals[_size] = std::move(v); // *(vals+_size) = v
        _size++;
    }

    void pop_back() {
        _size--;

    }


private:
    T *vals;
    int _size = 0;
    int _capacity = 100;
};


template<class T>
void swap(T &a, T &b) {
    a.swap(b);
}
