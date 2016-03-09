#include <boost/random.hpp> //乱数発生用ヘッダファイル
#include <iostream> //確認の出力用
#include <ctime> //乱数の種に time を使う場合に必要

double UniformRandom() //一様乱数を発生させる関数
{
  static boost::mt19937 gen( static_cast<unsigned int>(time(0)) );
  static boost::uniform_real<> dst(0,1);
  static boost::variate_generator< boost::mt19937&, boost::uniform_real<> > rand(gen, dst);
  return rand();
}

int main()
{
  for(int i=0; i<10; ++i)
	std::cout << UniformRandom() << std::endl;
}
