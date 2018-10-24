#include <iostream>
#include <fstream>

#include <random>
#include <algorithm>


template <class Head>
void message(std::ostream& stream,const char* string, Head head) {
    if (*string == '\0'){
        return;
    }
    if (*string == '%'){
        stream << head;
        string++;
        stream << string;
    }else{
        stream << string[0];
        string++;
        message(stream, string, head); // рекурсия
    }
}

template <class Head, class ... Tail>
void message(std::ostream& stream, const char* string, Head head, Tail ... tail) {
    if (*string == '\0'){
        return;
    }
    if (*string == '%'){
        stream << head;
        string++;
        message(stream, string, tail...); // рекурсия
    }else{
        stream << string[0];
        string++;
        message(stream, string, head, tail...); // рекурсия
    }


}

//int main(){
//    message(std::cout, "text1 % txt2 % txt3 % txt4 % txt 5", 2, 3.33, "HEY", "HEY");
//    return 0;
//}
