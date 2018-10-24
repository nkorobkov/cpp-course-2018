
#include "MyArray2D.h"

template<typename D>
class MyArray2D;

template <class T>
class MyMaskedArray2D{
private:
    MyArray2D<T> & initial;
    const MyArray2D<bool> & mask;
public:
    friend class MyArray2D<T>;


    MyMaskedArray2D<T>(MyArray2D <T> &initial, const MyArray2D<bool> &mask) : initial(initial), mask(mask){};

    MyArray2D<T> operator=(T val){
        for(int i =0; i< mask.h*mask.w; i++){
            if (mask.values[i]){
                initial.values[i] = val;
            }
        }
        return initial;
    }


};