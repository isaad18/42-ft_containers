#ifndef ITERATOR_HPP

#define ITERATOR_HPP

#include <cstring>

namespace ft{
	template <typename T>
	class iterator{
		private:
			T *ptr;
			size_t size;
			T current;
		public:
			iterator(){}
			iterator(T *ptr, size_t size) : ptr(ptr), size(size){ current = *ptr;}
			T &operator*(){ return current; }
			bool operator==(iterator other){ return this->current == other.current; }
			bool operator!=(iterator other){ return this->current != other.current; }
			iterator &operator++(){
				current = *(++ptr);
				return *this;
			}
			iterator operator++(int){
				iterator tmp(ptr, size);
				current = *(++ptr);
				return tmp;
			}
	};
}

#endif