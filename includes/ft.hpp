#ifndef GENERAL_HPP

#define GENERAL_HPP

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <memory>
#include <cstddef>
#include <string>
#include "enable_if.hpp"

namespace ft{
	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first1 > *first2)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <typename _InputIterator,typename _OutputIterator>
	 _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result){
		for (;__first != __last; __first++, (void) __result++)
			*__result = *__first;
		return __result;
	}

	template <typename _ForwardIterator,typename _Tp>
	inline void fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__value_){
		while (__first != __last){
			*__first = __value_;
			__first++;
		}
	}

	template <typename _ForwardIterator>
	inline size_t distance(_ForwardIterator __first, _ForwardIterator __last) {
		size_t dist = 0;
		while (__first != __last) {
			__first++;
			dist++;
		}
		return dist;
	}

	template <typename _InputIterator>
	bool equal( _InputIterator s1, _InputIterator s2, _InputIterator n){
		while (s1 != s2)
			if (*s1++ != *n++)
				return false;
		return true;
	}

	template <typename T>
	inline void realloc(T*& array, size_t oldSize, size_t newSize, size_t capacity, std::allocator<T> alloc) {
		T* newArray = alloc.allocate(newSize);
		if (oldSize > 0) {
			for (size_t i = 0; i < oldSize; i++)
				alloc.construct(newArray + i, array[i]);
		}
		if (capacity > 0) {
			for (size_t i = 0; i < capacity; i++) {
				alloc.destroy(array + i);
			}
			alloc.deallocate(array, capacity);
		}
		array = newArray;
	}

	template <typename T>
	inline void swaps(T &v1, T &v2){
		T tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
}

#endif
