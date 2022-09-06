#include <iostream>
#include <cstddef>

template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T>
{
  typedef T type;
};

template <class T, typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr>
void do_stuff(T& t)
{
  std::cout << "do_stuff integral\n";
}

template <class T, typename std::enable_if<std::is_class<T>::value, T>::type* = nullptr>
void do_stuff(T& t)
{ 
  // 일반적인 클래스 들을 받음
}

int main()
{

  do_stuff(2,);
}