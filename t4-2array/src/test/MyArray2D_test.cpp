

#include <gtest/gtest.h>
#include "../project/MyMaskedArray2D.h"
#include <iostream>
#include <string>

template <typename D>
bool checkValsEq(MyArray2D<D> &array, D* vals){
    for(int i = 0; i<array.h*array.w; i++){
        if (array.values[i] != *(vals+i)){
            return false;
        };
    }
    return true;
}

struct MyArray2D_test : public ::testing::Test {

    MyArray2D<int> a{2,3};
    MyArray2D<int> b{2,3};

    void SetUp() {
        int av[] = {-2, -1, 0, 1, 2, 3};
        a = MyArray2D<int>(2, 3, av);
        int bv[] = {3, 2, 1, 0, -1, -100};
        b = MyArray2D<int>(2, 3, bv);

    }


};


TEST_F(MyArray2D_test, Add) {
    int v[] = {1, 1, 1, 1, 1, -97};
    MyArray2D<int> r(2,3);
    r = a+b;
    EXPECT_TRUE(checkValsEq( r , v));
}

TEST_F(MyArray2D_test, Sub) {
    int v[] = {-5, -3, -1, 1, 3, 103};
    MyArray2D<int> r(2,3);
    r = a-b;
    EXPECT_TRUE(checkValsEq( r , v));
}

TEST_F(MyArray2D_test, Mul) {
    int v[] = {-6, -2, 0, 0, -2, -300};
    MyArray2D<int> r(2,3);
    r = a*b;
    EXPECT_TRUE(checkValsEq( r , v));
}




TEST_F(MyArray2D_test, more) {
    bool v[] = { 0,0,0,1,1,1};
    MyArray2D<bool> r(2,3);
    r = a>b;
    EXPECT_TRUE(checkValsEq( r , v));
}

TEST_F(MyArray2D_test, less) {
    bool v[] = {1,1,1,0,0,0};
    MyArray2D<bool> r(2,3);
    r = a<b;
    EXPECT_TRUE(checkValsEq( r , v));
}

TEST_F(MyArray2D_test, eq) {
    a.values[0] = b.values[0];
    bool v[] = {true,false,false,false,false,false};
    MyArray2D<bool> r(2,3);
    r = a==b;
    EXPECT_TRUE(checkValsEq( r , v));
}

TEST_F(MyArray2D_test, geter) {
    EXPECT_EQ(a(1,1), 2);
}

TEST_F(MyArray2D_test, masking) {
    bool mm[] = {true, false, true, true, false, true};
    MyArray2D<bool> m(2,3, mm);
    int v[] =  {3, -1, 3, 3, 2, 3};
    a(m) = 3;
    EXPECT_TRUE(checkValsEq( a , v));
}