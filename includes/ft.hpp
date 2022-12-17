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

namespace ft{
	template <typename _InputIterator,typename _OutputIterator>
	inline _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result){
		while (__first != __last){
			*__result = *__first;
			__first++;
			__result++;
		}
		return __result;
	}

	template <typename _ForwardIterator,typename _Tp>
	inline void fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__value_){
		while (__first != __last){
			*__first = __value_;
			__first++;
		}
	}

	template <typename _Type>
	inline _Type *alloc(size_t size){
		return (new _Type[size]);
	}

	template <typename T>
	inline void realloc(T*& array, size_t oldSize, size_t newSize)
	{
		T* newArray = alloc<T>(newSize);
		if (oldSize > 0){
			copy(array, array + oldSize, newArray);
			delete[] array;
		}
		array = newArray;
	}
}

#endif