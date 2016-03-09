#include <fstream>
#include <string>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>

class Person {
public:
  int         age;
  std::string name;

private:
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& archive, unsigned int version)
  {
	static_cast<void>(version); // No use
	archive & age;
	archive & name;
  }
};

int main()
{
  std::ofstream ofs("C:/person.txt");
  boost::archive::text_oarchive oarchive(ofs);

  Person person;
  person.age  = 22;
  person.name = "Akira";

  // クラス情報をテキスト出力
  oarchive << static_cast<const Person&>(person);

  return 0;
}
