#include <myadd.h>
#include <iostream>
#include "helper.h"

struct MyStruct {
    // some other var
    int a;
    // some var
    int b;
};

int main() {
    MyStruct tt;
    MyAdd add_obj;
    Helper h;
    h.help();
    h.help();
    h.dummy();
    add_obj.add(3, 4);
    add_obj.addnew(4, 10);
    std::cout << "Addition Result:" << add_obj.add(1, 1) << std::endl;
}
