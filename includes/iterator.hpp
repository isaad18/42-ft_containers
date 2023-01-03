#ifndef ITERATOR_HPP

#define ITERATOR_HPP

#include <cstring>

namespace ft{
	template <typename T>
	class iterator{
		private:
			T *ptr;
		public:
			iterator(): ptr(NULL){}
			iterator(T *ptr) : ptr(ptr){}
			template<class U>
			iterator(const U &other): ptr(const_cast<T *>(other.getptr())){}
			template<class U>
			iterator(U &other): ptr((other.getptr())){}

			T &operator*(){ return *getptr(); }
			T &operator*() const{ return *getptr(); }
			bool operator==(iterator other) const{ return &(*(this->ptr)) == &(*(other.getptr())); }
			bool operator!=(iterator other) const{ return &(*(this->ptr)) != &(*(other.getptr())); }
			bool operator>(iterator other) const{ return &(*(this->ptr)) > &(*(other.getptr())); }
			bool operator<(iterator other) const{ return &(*(this->ptr)) < &(*(other.getptr())); }
			T *getptr() const{ return ptr; }
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
			iterator operator+(int n){
				iterator tmp(ptr);
				tmp.ptr += n;
				return tmp;
			}
			iterator operator-(int n){
				iterator tmp(ptr);
				tmp.ptr -= n;
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