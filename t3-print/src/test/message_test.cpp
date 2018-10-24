

#include <gtest/gtest.h>
#include "../project/main.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



TEST(testMessage, myTest){
std::stringstream stream;
message(stream, "% + % = %", "a", 1, 3.0);
EXPECT_EQ(stream.str(), "a + 1 = 3");
}

TEST(testMessage, myTest2){
    std::stringstream stream;
    message(stream, "text1 % txt2 % txt3 % txt4 % txt 5", 2, 3.33, "HEY", "HEY");
    EXPECT_EQ(stream.str(), "text1 2 txt2 3.33 txt3 HEY txt4 HEY txt 5");
}

TEST(testUneven, less){
    std::stringstream stream;
    message(stream, "text1 % txt2 % txt3 % txt4 % txt 5", 2, 3.33, "HEY");
    EXPECT_EQ(stream.str(), "text1 2 txt2 3.33 txt3 HEY txt4 % txt 5");
}

TEST(testUneven, more){
    std::stringstream stream;
    message(stream, "text1 % txt2 % txt3 % txt4 % txt 5", 2, 3.33, "HEY", "HEY", "EXTRA");
    EXPECT_EQ(stream.str(), "text1 2 txt2 3.33 txt3 HEY txt4 HEY txt 5");
}
