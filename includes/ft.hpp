#ifndef GENERAL_HPP

#define GENERAL_HPP

#include <algorithm>
#include <climits>
// #include <compare>
#include <cstdlib>
#include <cstring>
// #include <initializer_list>
// #include <iosfwd> // for forward declaration of vector
// #include <limits>
// #include <memory>
// #include <stdexcept>
// #include <type_traits>
// #include <version>
#include <iostream>

namespace ft{
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
	inline size_t distance(_ForwardIterator __first, _ForwardIterator __last){
		size_t dist = 0;
		size_t it = 0;
		while (__first != __last){
			__first++;
			dist++;
		}
		return ++dist;
	}

	template <typename _Type>
	inline _Type *alloc(size_t size){
		return (new _Type[size]);
	}

	template <typename T>
	inline void realloc(T*& array, size_t oldSize, size_t newSize, size_t capacity)
	{
		T* newArray = alloc<T>(newSize);
		if (capacity > 0){
			copy(array, array + oldSize, newArray);
			ft::fill(newArray + oldSize, newArray + newSize, 0);
			if (capacity > 0)
				delete[] array;
		}
		array = &(*newArray);
	}

	template <typename T>
	inline void swap(T &v1, T &v2){
		T tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
}

#endif