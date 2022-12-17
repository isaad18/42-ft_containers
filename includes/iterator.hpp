#ifndef ITERATOR_HPP

#define ITERATOR_HPP

#include <cstring>

namespace ft{
	template <typename T>
	class iterator{
		private:
			T *ptr;
			size_t size;
			// T current;
		public:
			iterator(T **ptr, size_t size) : ptr(*ptr), size(size){}
			T &operator*(){ return *ptr; }
			bool operator==(iterator other){ return *(this->ptr) == *(other.ptr); }
			bool operator!=(iterator other){ return *(this->ptr) != *(other.ptr); }
			iterator &operator++(){
				++ptr;
				return *this;
			}
			iterator operator++(int){
				iterator tmp(&ptr, size);
				++ptr;
				return tmp;
			}
	};

	template <typename T>
	class const_iterator{
		private:
			T *ptr;
			size_t size;
			T current;
		public:
			const_iterator(T* ptr, size_t size) : ptr(ptr), size(size){ current = *ptr;}
			T &operator*()const{ return current; }
			bool operator==(const const_iterator other) const{ return this->current == other.current; }
			bool operator!=(const const_iterator other) const{ return this->current != other.current; }
			const_iterator &operator++() const{
				current = *(++ptr);
				return *this;
			}
			const_iterator operator++(int) const{
				const_iterator tmp(ptr, size);
				current = *(++ptr);
				return tmp;
			}
	};
}

#endif