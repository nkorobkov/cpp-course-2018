#include <iostream>
#ifndef T4_GUARD_MYGUARD_H
#define T4_GUARD_MYGUARD_H

struct MyGuard {
    std::ostream & _x;
    std::ios_base::fmtflags flags;
    char fill;


    MyGuard(std::ostream& x): _x(x){
        flags = x.flags();
        fill = x.fill();
    };

    ~MyGuard() {
        _x.flags(flags);
        _x.fill(fill);
    }
    MyGuard(const MyGuard&) = delete;
    MyGuard& operator=(const MyGuard&) = delete;
};


#endif //T4_GUARD_MYGUARD_H
