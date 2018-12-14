#include <string>
#include <unordered_set>

struct User {
    int id;
    std::string first_name, last_name;

    User(int id, std::string &&first_name, std::string &&last_name) : id(id), first_name(std::move(first_name)),
                                                                      last_name(std::move(last_name)) {};
    bool operator==(const User &p) const {
        return id == p.id;
    }
};


template<>
struct std::hash<User> {
    typedef size_t result_type;
    typedef User argument_type;

    result_type operator()(const argument_type &x) const {
        return static_cast<result_type>(x.id);
    }
};


struct Group {
    int id;
    std::string name;
    std::unordered_set<User> users;

    Group(int id, std::string &&name) : id(id), name(std::move(name)) {}
};


namespace std {


    template<class T>
    struct MyTrait;

    template<>
    struct MyTrait<User> {
        static int size(const User &x) {
            return sizeof(x.id) + x.first_name.size() + x.last_name.size();
        }
    };


    template<>
    struct MyTrait<Group> {
        static int size(const Group &x) {
            int size = sizeof(x.id) + x.name.size();
            for (auto user: x.users)
                size += MyTrait<User>::size(user);
            return size;
        }
    };
}