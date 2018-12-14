#include <iostream>
#include <myproject/t3-print/message.h>
//#include <fstream>
//#include <random>
//#include <algorithm>



int main(){
    message(std::cout, "text1 % txt2 % txt3 % txt4 % txt 5", 2, 3.33, "HEY", "HEY");
    return 0;
}
