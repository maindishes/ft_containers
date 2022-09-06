#include <iostream>

int negate(unsigned int i) { return -i; }

// template <typename T>
// typename T::value_type negate(const T& t) {
//   return -T(t);
// }
template <typename T>
void negate(const T& t) {
  typename T::value_type n = -t();
}
int main()
{
  std::cout << negate(42) << std::endl;
}