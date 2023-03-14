#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP
#include <string>

namespace ft
{
	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };
	struct false_type { static const bool value = false;};
	struct true_type { static const bool value = true;};
	
	template <class T> struct is_integral: public ft::false_type {};
	template <> struct is_integral<bool>: public ft::true_type {};
	template <> struct is_integral<char>: public ft::true_type {};
	template <> struct is_integral<signed char>: public ft::true_type {};
	template <> struct is_integral<unsigned char>: public ft::true_type {};
	template <> struct is_integral<wchar_t>: public ft::true_type {};
	template <> struct is_integral<short>: public ft::true_type {};
	template <> struct is_integral<unsigned short>: public ft::true_type {};
	template <> struct is_integral<int>: public ft::true_type {};
	template <> struct is_integral<unsigned int>: public ft::true_type {};
	template <> struct is_integral<long>: public ft::true_type {};
	template <> struct is_integral<unsigned long>: public ft::true_type {};
	template <> struct is_integral<long long>: public ft::true_type {};
	template <> struct is_integral<unsigned long long>: public ft::true_type {};
	template <> struct is_integral<std::string>: public ft::true_type {};
}

#endif
