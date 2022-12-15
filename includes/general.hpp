#ifndef GENERAL_HPP

#define GENERAL_HPP

#include<iostream>
#include<string>
#include <exception>
#include <algorithm>

template <typename T>
void _reallocate(T*& array, size_t oldSize, size_t newSize)
{
    T* newArray = new T[newSize];
	if (oldSize > 0){
	    std::copy(array, array + oldSize, newArray);
    	delete[] array;
	}
    array = newArray;
}

#endif