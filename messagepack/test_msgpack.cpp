#include <msgpack.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

/**
   http://ota42y.com/blog/2014/08/05/msgpack/b
   http://frsyuki.hatenablog.com/entry/20080914/p2
   g++ -std=c++11 test_msgpack.cpp -lmsgpack -o test_msgpack
 **/


class request_t {
public:
    // デシリアライズ用関数
    void message_unpack(msgpack::type::tuple<
                        bool,
                        std::string,
                        std::vector<int>,
                        uint32_t> t )
    {
        m_is_notify = t.get<0>();
        m_method = t.get<1>();
    }
}

int test_msgpack3() {
    char data[] = {
        0x94,
        0xc3,
        0xa3,
        0x67, 0x65, 0x74,
        0x93,
        0x1, 0x2, 0x3,
        0xa
    };

    // deserialize to msgpack::object
    msgpack::zone z;
    msgpack::object obj = msgpack::unpack(data, sizeof(data), z);
    std::cout << "test: " << obj << std::endl;

    // trainform msgpack::object to static type
    msgpack::type::tuple<
        bool,
        std::string,
        std::vector<int>,
        uint32_t> request;
    msgpack::convert(request, obj);

    // 静的型からシリアライズしてバイト列にする
    // msgpack::object（タグ付きのunion）からmsgpack::type::tuple<...>という型に変換
    std::stringstream output;
    msgpack::pack(output, request);

    // 再度デシリアライズして表示
    std::string str = output.str();
    msgpack::object reobj = msgpack::unpack(str.data(), str.size(), z);
    std::cout << "ok? : " << reobj << std::endl;

    return 0;
    
}


/*
int test_msgpack2() {
    msgpack::type::tuple<int, bool, std::string> src(1, true, "example");
    // serialize the object into the buffer.
    // any classes that implements write(const char*, size_t) can be a buffer.
    std::stringstream buffer;
    msgpack::pack(buffer, src);

    // send the buffer
    buffer.seekg(0);

    // deserialize the buffer into msgpack::object instance
    std::string str(buffer.str());

    msgpack::object_handle oh = msgpack::unpack(str.data(), str.size());
}
*/


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
    test_msgpack3();
}

