#include <iostream>
#include <fstream>

#include "User.h"
#include <algorithm>



int main(){
    User a = User(27, "Nikita", "Korobkov");
    User b = User(21, "Anna", "Shaleva");

    Group c = Group(1, "c++");

    c.users.insert(a);
    c.users.insert(b);

    std::cout<<"User size --> "<<std::MyTrait<User>::size(a)<<" "<<std::MyTrait<User>::size(b)<< " Group size --> " <<std::MyTrait<Group>::size(c)<<"\n";

    for (auto user: c.users){
        std::cout<<user.first_name<<"\n";
    }

    return 0;
}
