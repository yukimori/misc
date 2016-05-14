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

// User-defined classes
// ref:https://github.com/msgpack/msgpack-c/blob/cpp-0.5.8/QUICKSTART-CPP.md
// http://qiita.com/yohm13/items/49d41fdf4fe49f34b574
class Myclass {
private:
    std::string m_str;
    std::vector<int> m_vec;

public:
    // 引数なしのコンストラクタがないとエラーになる
    void print_member() {
        std::cout << m_str << std::endl;
    }
    Myclass(){
    }
    Myclass(std::string str, int value1) {
        m_str = str;
        m_vec.push_back(value1);
    }
    ~Myclass(){ }
    MSGPACK_DEFINE(m_str, m_vec);
};

int test_msgpack5() {
    std::vector<Myclass> vec;
    vec.push_back(Myclass("test Myclass name", 14));

    // Myclassをシリアライズする
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, vec);

    msgpack::unpacked msg;
    msgpack::unpack(&msg, sbuf.data(), sbuf.size());

    msgpack::object obj = msg.get();

    // Myclassに直接変換することができる
    std::vector<Myclass> rvec;
    obj.convert(&rvec);

    rvec[0].print_member();
}

/*
// コンパイルエラーになる根本的にやり方が古い？
// 自作クラス
// msgpack_unpack,msgpack_packを実装すると当該クラスへのデシリアライズ、シリアライズができるようになる
class request_t {
public:
    // デシリアライズ用関数
    void msgpack_unpack(msgpack::type::tuple<
                        bool,
                        std::string,
                        std::vector<int>,
                        uint32_t> t )
    {
        m_is_notify = t.get<0>();
        m_method    = t.get<1>();
        m_params     = t.get<2>();
        m_id        = t.get<3>();
    }

    // シリアライズ用関数
    // constメンバ関数
    // ref:http://qiita.com/takeh1k0/items/b6587734f0a88951f8d4
    msgpack::type::tuple<
        book,
        std::string,
        std::vector<int>,
        uint32_t> msgpack_pack() const
    {
        return msgpack::type::make_tuple(m_is_notify, m_method, m_params, m_id);
    }

private:
    bool             m_is_notify;
    std::string      m_method;
    std::vector<int> m_params;
    uint32_t         m_id;
};

int test_msgpack4() {
    // サンプルデータ
    // 内容は [true, "get", [1,2,3], 10]
    char data[] = {
        0x94,
        0xc3,
        0xa3,
        0x67, 0x65, 0x74,
        0x93,
        0x1, 0x2, 0x3,
        0xa };

    // デシリアライズする
    msgpack::zone z;
    msgpack::object obj = msgpack::unpack(data, sizeof(data), z);

    // マイクラスに変換
    request_t request;
    msgpack::convert(request, obj);

    // マイクラスからシリアライズ
    std::stringstream output;
    msgpack::pack(output, request);

    // もう一度デシリアライズして表示
    std::string str = output.str();
    msgpack::object reobj = msgpack::unpack(str.data(), str.size(), z);
    std::cout << "ok? : " << std::endl;

    return 0;
}
*/

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
    test_msgpack5();
}

