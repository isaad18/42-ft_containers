#ifndef ITERATOR_HPP

#define ITERATOR_HPP

#include <cstring>

namespace ft{
	template <typename T>
	class iterator{
		private:
			// T current;
		public:
			T *ptr;
			iterator(T *ptr) : ptr(ptr){}
			// iterator(T const *ptr, size_t size) : ptr(*ptr), size(size){}
			T &operator*(){ return *ptr; }
			T &operator*() const{ return *ptr; }
			bool operator==(iterator other) const{ return &(*(this->ptr)) == &(*(other.ptr)); }
			bool operator!=(iterator other) const{ return &(*(this->ptr)) != &(*(other.ptr)); }
			bool operator>(iterator other) const{ return &(*(this->ptr)) > &(*(other.ptr)); }
			bool operator<(iterator other) const{ return &(*(this->ptr)) < &(*(other.ptr)); }
			iterator &operator++(){
				++ptr;
				return *this;
			}
			iterator operator++(int){
				iterator tmp(ptr);
				++ptr;
				return tmp;
			}
			iterator &operator--(){
				--ptr;
				return *this;
			}
			iterator operator--(int){
				iterator tmp(ptr);
				--ptr;
				return tmp;
			}
	};

	// template <typename T>
	// class const_iterator{
	// 	private:
	// 		T *ptr;
	// 		size_t size;
	// 		// T current;
	// 	public:
	// 		const_iterator(T **ptr, size_t size) : ptr(*ptr), size(size){}
	// 		T &operator*() const{ return *ptr; }
	// 		bool operator==(const_iterator other){ return *(this->ptr) == *(other.ptr); }
	// 		bool operator!=(const_iterator other){ return *(this->ptr) != *(other.ptr); }
	// 		const_iterator &operator++(){
	// 			++ptr;
	// 			return *this;
	// 		}
	// 		const_iterator operator++(int){
	// 			const_iterator tmp(&ptr, size);
	// 			++ptr;
	// 			return tmp;
	// 		}
	// };
}

#endif