

#include <pficommon/lang/shared_ptr.h>

#include <string>
#include <iostream>
#include <vector>

struct Object
{
    std::string str;

    Object(const std::string& InitStr) {
        str=InitStr;
    }

    /** デストラクタ
                デストラクタが呼ばれた事を表すメッセージを表示
    */
    ~Object()
    {
        std::cout << "call "<< str <<"::~Object():" << std::endl;
    }
};
//毎回打つには長いのでtypedef
typedef pfi::lang::shared_ptr<Object> obj_ptr;

int main(int argc, char *argv[])
{
    if(1) {    //ブロック1
        obj_ptr Array[]={
            obj_ptr(new Object("Obj0")),
            obj_ptr(new Object("Obj1")),
            obj_ptr(new Object("Obj2")) };
        if(1)
        {
            //ブロック2
            std::vector<obj_ptr> v;
            v.insert(v.begin(), Array, Array+3);

            //ブロック2から抜ける(vectorが破棄される)
            std::cout << "break Block2" << std::endl;
        }

        //ブロック1から抜ける(配列が破棄される)
        std::cout << "break Block1" << std::endl;
    }
    std::cout << "return" << std::endl;
    return 0;
}
