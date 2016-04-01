#include <iostream>
#include <vector>
#include <algorithm>

/**
   http://not522.hatenablog.com/entry/2016/03/20/005946
   ナップサック問題を以下の方法でとく
   順番に詰め込む(basic)
   ビームサーチ
   焼きなまし
 **/

void basic(const int w[], const int v[],  int num, int weight) {
  // 今までに入れた物の重さの総和
  int s = 0;
  // 今までに入れた物の価値の総和
  long t = 0;

  //入れるだけ入れる
  for (int i=0; i<num; ++i) {
	if (s + w[i] <= weight) {
	  s += w[i];
	  t += v[i];
	}
  }

  //結果
  std::cout << "basic socre:" << t << std::endl;
}

void beamsearch(const int* w, const int* v,  int num, int weight) {
  //ビーム幅
  const int BEAM = 100;

  std::vector<std::pair<long long, int>> curr ;
  // c++11 support emplace_back
  curr.emplace_back(0, 0);

  //ビームサーチ
  for(int i=0; i<num; ++i) {
	//次の状態（価値、重さ）
	std::vector<std::pair<long long, int>> next;
	for(const auto& s : curr) {
	  next.emplace_back(s);
	  if(s.second + w[i] <= weight) {
		next.emplace_back(s.first + v[i], s.second + w[i]);
	  }
	}
	//価値が大きい順に並び替え
	std::sort(next.rbegin(), next.rend());
	//状態をビーム幅に減らす
	if (next.size() > BEAM) {
	  next.resize(BEAM);
	}
	curr = std::move(next);
  }
  //結果
  std::cout << "beamsearch socre:" << curr[0].first << std::endl;
}

int main()
{
  //個数
  const int N = 100000;
  //ナップサックの大きさ
  const int W = 100000;

  // 重さ、価値
  int w[N], v[W];
  for (int i=0; i<N; ++i) {
	std::cin >> w[i] >> v[i];
  }

  basic(w, v, N, W);
  beamsearch(w, v, N, W);
  
}

