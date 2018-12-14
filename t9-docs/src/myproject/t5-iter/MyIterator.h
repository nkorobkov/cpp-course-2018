#ifndef T5_ITER_MYITERATOR_H
#define T5_ITER_MYITERATOR_H


#include <ostream>
#include <string>
#include <iterator>

template<typename T>
class MyIterator : public std::iterator<std::output_iterator_tag, void, void, void, void> {


private:
    std::ostream &stream;
    int N = 0;
    int i = 0;

public:

    MyIterator(std::ostream &stream, int N) : stream(stream), N(N), i(0) {}

    MyIterator &operator=(const T &value) {
        i++;
        if (i == N ) {
            stream << value << " ";
            i = 0;
        }
        return *this;
    }

    MyIterator &operator*() {
        return *this;
    }

    MyIterator &operator++() {
        return *this;
    }

    MyIterator &operator++(int) {
        return *this;
    }
    ~MyIterator() = default;
};


#endif //T5_ITER_MYITERATOR_H
