#pragma once
#include <iostream>

/*
  ref:
  http://jumble-note.blogspot.jp/2012/08/c.html
 */

namespace Types
{
  //特定のクラスを継承しているか調べる
  template<class Base, class Sub>
  class IsBaseOf
  {
	typedef int T ;
	struct F { 
	  int i, j;
	} ;
  private:
	static Sub *d ;
	static T check(const Base &) ;
	static F check(...) ;
  public:
	static const bool value = sizeof(check(*d)) == sizeof(T) ;
  } ;

  //あとでオーバーロード解決に使用
  template<bool B, typename T>
  struct enable {typedef T type ;} ;
  template<typename T>
  struct enable<false, T> { } ;
  template<bool B, typename T>
  struct disable : public enable<!B, T> { } ;
}

namespace Serialization
{
  class Archive ;

  //このクラスを継承するとシリアライズ可能になる
  class Serializable
  {
  public:
	virtual void serialize(Archive &data) = 0 ;
  } ;

  //シリアライザ
  class Archive
  {
  private:
	void *data ;
	bool _load ;
	
	//書き込み処理
	template<typename T>
	inline void write(T &object) {
	  static_cast<std::ostream *>(data)->write(reinterpret_cast<char *>(object), sizeof(*object)) ;
	}
	template<typename T>
	inline void write(T *object) {
	  static_cast<std::ostream *>(data)->write(reinterpret_cast<char *>(object), sizeof(*object)) ;
	}
	template< >
	inline void write<Serializable>(Serializable &object) {
	  object.serialize(*this) ;
	}
	template< >
	inline void write<Serializable>(Serializable *object) { object->serialize(*this); }

	/* 読み込み処理 */
	template<typename T>
	inline void read(T &object) { static_cast<std::istream *>(data)->read(reinterpret_cast<char *>(&object), sizeof(object)); }
        
	template<typename T>
	inline void read(T *object) { static_cast<std::istream *>(data)->read(reinterpret_cast<char *>(object), sizeof(*object)); }

	template<>
	inline void read<Serializable>(Serializable &object) {
	  object.serialize(*this);
	}

	template<>
	inline void read<Serializable>(Serializable *object) {
	  object->serialize(*this);
	}

	template<typename T>
	inline Archive &serialize(T &object, typename Types::enable<Types::IsBaseOf<Serializable, T>::value, T>::type* = 0) {
	  _load ? read<Serializable>(object) : write<Serializable>(object); return *this;
	}

	template<typename T>
	inline Archive &serialize(T &object, typename Types::disable<Types::IsBaseOf<Serializable, T>::value, T>::type* = 0) {
	  _load ? read(object) : write(object); return *this;
	}

	template<typename T>
	inline Archive &serialize(T *object, typename Types::enable<Types::IsBaseOf<Serializable, T>::value, T>::type* = 0) {
	  _load ? read<Serializable>(object) : write<Serializable>(object); return *this;
	}

	template<typename T>
	inline Archive &serialize(T *object, typename Types::disable<Types::IsBaseOf<Serializable, T>::value, T>::type* = 0) {
	  _load ? read(object) : write(object); return *this;
	}

  public:
	Archive(std::istream *stream) : _load(true), data(stream) { }
	Archive(std::ostream *stream) : _load(false), data(stream) { }
	Archive(std::istream &stream) : _load(true), data(&stream) { }
	Archive(std::ostream &stream) : _load(false), data(&stream) { }

	template<typename T>
	inline Archive &operator +(T &object) { return serialize(object); }

	template<typename T>
	inline Archive &operator +(T *object) { return serialize(object); }
  };
} ;

class Something : public Serializable
{
private:
  int num1 ; //シリアライズ対
  unsigned int num2 ; //シリアライズ対
  short num3 ; //シリアライズ対象にならない
public:
  void serialize(Archive &data) {
	data + num1 + num2 ;
  } ;
} ;

int main() {
  std::ofstream ofs("test.bin", std::ios_base::binary) ;
  Serialization::Archive writer(ofs) ;

  Something s, t ;
  writer + s + t ;
}


