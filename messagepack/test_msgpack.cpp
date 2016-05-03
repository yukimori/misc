#include <msgpack.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct User {
    User(std::string name, int id, std::vector<int> follower)
            : name(name)
            , id(id)
            , follower_id(follower)
    {}

    // 引数無しのコンストラクタは必須
    User()
            : id(0)
    {}

    MSGPACK_DEFINE(name, id, follower_id);
    std::string name;
    int id;
    std::vector<int> follower_id;

    std::string toString() {
        std::string ret = "name; ";
        ret += name;
        ret += " id: ";
        ret += std::to_string(id);
        ret += " follower: ";
        for ( int i=0; i < follower_id.size(); ++i ) {
            ret += std::to_string(follower_id[i]);
            ret += " ";
        }
        return ret;
    }
};

int test_msgpack1() {
    // generate sampledata
    std::vector<int> follower_1;
    follower_1.push_back(1);
    follower_1.push_back(2);

    std::vector<int> follower_2;
    follower_2.push_back(2);

    std::vector<User> users;
    users.push_back(User("user1", 1, follower_1));
    users.push_back(User("user2", 2, follower_2));

    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, users);

    std::ofstream myFile("cpp_data.bin", std::ios::out | std::ios::binary);
    myFile.write(sbuf.data(), sbuf.size());
    myFile.close();

    // read data from file
    char buffer[1000];
    std::ifstream inFile("cpp_data.bin", std::ios::in | std::ios::binary);
    inFile.read(buffer, 1000);
    inFile.close();

    msgpack::unpacked msg;
    msgpack::unpack(&msg, buffer, 1000);

    msgpack::object obj = msg.get();
    std::vector<User> load_users;
    obj.convert(&load_users);
    for ( int i=0; i < load_users.size(); ++i ) {
        std::cout << load_users[i].toString() << std::endl;
    }
    return 0;
}

int main(void) {
    test_msgpack1();
}

