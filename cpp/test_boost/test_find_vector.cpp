#include <iostream>
#include <vector>

#include <boost/range/algorithm.hpp>

using namespace std;

int main(int argc, char *argv[]) {
    vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    vector<int>::iterator it = boost::find(v, 3);
    cout << *it << endl;

    it = boost::find(v, 100);
    cout << *it << endl;
    cout << (it == v.end()) << endl;
    // cout << it << endl;

    return 0;
}
