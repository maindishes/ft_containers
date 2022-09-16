#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

#include <cstdint>

namespace ft
{
/**
 * @brief Enable type if condition is met
 * The type T is enabled as member type enable_if::type if bool is true.
 * Otherwise, enable_if::type is not defined.
 */
template <bool, typename T = void>
struct enable_if { };

template <typename T>
struct enable_if<true, T> { typedef T type; };

template <bool B, typename T = void, typename U = void>
struct conditional { };

template <typename T, typename U>
struct conditional<true, T, U> { typedef T type; };

template <typename T, typename U>
struct conditional<false, T, U> { typedef U type; };

struct false_type {
	typedef bool value_type;
	typedef false_type type;
	static const value_type value = false;
};

struct true_type {
	typedef bool value_type;
	typedef true_type type;
	static const value_type value = true;
};

/**
 * @brief Trait class that identifies whether T is an integral type.
 */
template <typename T>
struct is_integral {
	typedef false_type Integral;
};

template <>
struct is_integral<bool> {
	typedef true_type Integral;
};

template <>
struct is_integral<char> {
	typedef true_type Integral;
};

template <>
struct is_integral<char16_t> {
	typedef true_type Integral;
};

template <>
struct is_integral<char32_t> {
	typedef true_type Integral;
};

template <>
struct is_integral<wchar_t> {
	typedef true_type Integral;
};

template <>
struct is_integral<signed char> {
	typedef true_type Integral;
};

template <>
struct is_integral<short int> {
	typedef true_type Integral;
};

template <>
struct is_integral<int> {
	typedef true_type Integral;
};

template <>
struct is_integral<long int> {
	typedef true_type Integral;
};

template <>
struct is_integral<__int64_t> {
	typedef true_type Integral;
};

template <>
struct is_integral<unsigned char> {
	typedef true_type Integral;
};

template <>
struct is_integral<unsigned short int> {
	typedef true_type Integral;
};

template <>
struct is_integral<unsigned int> {
	typedef true_type Integral;
};

template <>
struct is_integral<unsigned long int> {
	typedef true_type Integral;
};

template <>
struct is_integral<__uint64_t> {
	typedef true_type Integral;
};
} // namespace ft

#endif

_capacity = 0;
for (InputIterator it = first; it != last; it++)
{
    _capacity++;
}
_data = _allocator.allocate(_capacity);
for (_size = 0; _size < _capacity; _size++)
{
    _allocator.construct(_data + _size, *first++);
}