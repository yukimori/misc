#include <string>
#include <iostream>
#include <fstream>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp> 
#include <boost/serialization/string.hpp> 
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
//std::stringクラスをシリアル化するために必要なヘッダ

/**
元のクラスをシリアル化できるようにコードを追加したものが本クラス
http://img.atwikiimg.com/www31.atwiki.jp/lafe/pub/boost_serialization/boost_serialization.html
class Student {
private:
  std::string name_ ;
  int age_ ;
} ;
 **/

class Student {
public:
  std::string name ;
  int age ;

private:
  //boost::serializationがprivateメンバであるserialize関数にアクセスするためのfriend指定
  friend class boost::serialization::access; 
  // serialize関数はpublicにしてはいけない
  // arは出力先・入力元を表す引数
  // versionは保存形式のバージョンを示す番号
  template<class Archive>
  void serialize(Archive& ar, unsigned int version) 
  {
	static_cast<void>(version); //No Use
	ar & name ;  //メンバをarに出力・読込する
	ar & age ; // &が出力・読込演算子 <<,>>も使える
  }

} ;

//mainがないとコンパイルできない
int main()
{
  Student student;
  student.name="Motoki";
  student.age=32 ;
	

  //出力アーカイブの作成
  std::ofstream ofs("output.txt");
  boost::archive::text_oarchive oa(ofs);

  //ファイルに書き出し
  oa << static_cast<const Student&>(student);
  ofs.close();

  //入力アーカイブの作成
  std::ifstream ifs("output.txt");
  boost::archive::text_iarchive ia(ifs);

  //ファイルから読込
  ia >> student ;
  ifs.close();

  return 0;
}
