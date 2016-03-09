#include <iostream>
#include <boost/foreach.hpp>
#include <vector>
 
#include <boost/range/algorithm.hpp>
 
using namespace std;
 
void dump(vector<int>& v)
{
  BOOST_FOREACH(int x, v) {
	cout << x << endl;
  }
}
 
int main (int argc, char *argv[])
{
  vector<int> v;
     
  v.push_back ( 3 );
  v.push_back ( 4 );
  v.push_back ( 1 );
  v.push_back ( 2 );
     
  cout << "Before sort" << std::endl;
  dump (v);
     
  boost::sort(v);
     
  cout << "After sort" << std::endl;
  dump (v);
  return 0;
}
