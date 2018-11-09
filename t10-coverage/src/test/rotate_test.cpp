#include <gtest/gtest.h>
#include <project/Pair.h>



TEST(rotate_test, one)
{
    Pair p = {3,4};
    auto r = rotate(p, 1);
    EXPECT_EQ(r.x, -4);
    EXPECT_EQ(r.y, 3);
}

TEST(rotate_test, two)
{
Pair p = {3,4};
auto r = rotate(p, 2);
EXPECT_EQ(r.x, -3);
EXPECT_EQ(r.y, -4);
}

TEST(rotate_test, three)
{
Pair p = {3,4};
auto r = rotate(p, 3);
EXPECT_EQ(r.x, 4);
EXPECT_EQ(r.y, -3);
}

TEST(rotate_test, four)
{
Pair p = {3,4};
auto r = rotate(p, 4);
EXPECT_EQ(r.x, 3);
EXPECT_EQ(r.y, 4);
}

