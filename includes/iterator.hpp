#ifndef iterator_HPP

#define iterator_HPP

#include <cstring>
#include "ft.hpp"

namespace ft{
	template <typename T>
	class iterator{
		private:
			T *ptr;
		public:
			typedef ptrdiff_t difference_type;
		public:
			iterator(): ptr(NULL){}
			iterator(T *ptr) : ptr(ptr){}
			template<class U>
			iterator(const iterator<U> &other): ptr(const_cast<T *>(other.base())){}
			T &operator=(T &other){ ptr = other.base(); return *this; }

			T &operator*(){ return *base(); }
			T &operator*() const{ return *base(); }
			bool operator==(iterator other) const{ return &(*(this->ptr)) == &(*(other.base())); }
			bool operator!=(iterator other) const{ return &(*(this->ptr)) != &(*(other.base())); }
			bool operator>(iterator other) const{ return &(*(this->ptr)) > &(*(other.base())); }
			bool operator<(iterator other) const{ return &(*(this->ptr)) < &(*(other.base())); }
			T *base() const{ return ptr; }
			T &operator[](difference_type num) {
				return (*(ptr + num));
			}
			T *operator->() const { return ptr; }
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
			iterator operator+(int n) const{
				iterator tmp(ptr);
				tmp.ptr += n;
				return tmp;
			}
			iterator operator-(int n) const{
				iterator tmp(ptr);
				tmp.ptr -= n;
				return tmp;
			}
			iterator &operator+=(int n){
				ptr += n;
				return *this;
			}
			iterator &operator-=(int n){
				ptr -= n;
				return *this;
			}
	};

	template <class T>
	class reverse_iterator{
		private:
			T *ptr;
		public:
			typedef ptrdiff_t difference_type;
		public:
			reverse_iterator(): ptr(NULL){}
			reverse_iterator(T ptr) : ptr(ptr.base()){}
			template<class U>
			reverse_iterator(U ptr) : ptr(ptr){}
			template<class U>
			reverse_iterator(const iterator<U> &other): ptr(const_cast<T *>(other.base())){}
			template<class U>
			reverse_iterator(const reverse_iterator<U> &other): ptr(const_cast<T *>(other.base())){}
			T &operator=(T &other){ ptr = other.base(); return *this; }
			T &operator*(){ return *base(); }
			T &operator*() const{ return *base(); }
			bool operator==(reverse_iterator other) const{ return &(*(this->ptr)) == &(*(other.base())); }
			bool operator!=(reverse_iterator other) const{ return &(*(this->ptr)) != &(*(other.base())); }
			bool operator>(reverse_iterator other) const{ return &(*(this->ptr)) > &(*(other.base())); }
			bool operator<(reverse_iterator other) const{ return &(*(this->ptr)) < &(*(other.base())); }
			T *base() const{ return ptr; }
			T &operator[](difference_type num) {
				return (*(ptr + num));
			}
			T *operator->() const { return ptr; }
			reverse_iterator &operator++(){
				--ptr;
				return *this;
			}
			reverse_iterator operator++(int){
				reverse_iterator tmp(ptr);
				--ptr;
				return tmp;
			}
			reverse_iterator &operator--(){
				++ptr;
				return *this;
			}
			reverse_iterator operator--(int){
				reverse_iterator tmp(ptr);
				++ptr;
				return tmp;
			}
			reverse_iterator operator+(int n) const{
				reverse_iterator tmp(ptr);
				tmp.ptr -= n;
				return tmp;
			}
			reverse_iterator operator-(int n) const{
				reverse_iterator tmp(ptr);
				tmp.ptr += n;
				return tmp;
			}
			reverse_iterator &operator+=(int n){
				ptr -= n;
				return *this;
			}
			reverse_iterator &operator-=(int n){
				ptr += n;
				return *this;
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

// template <typename T>
// ft::iterator<T> operator==(ft::iterator<T> &lhs, ft::iterator<T> &rhs){ return lhs.base() == rhs.base(); }

// template <typename T, typename T1>
// ft::iterator<T> operator==(ft::iterator<T> &lhs, ft::iterator<T1> &rhs){ return lhs.base() == rhs.base(); }

// template <typename T>
// ft::iterator<T> operator!=(ft::iterator<T> &lhs, ft::iterator<T> &rhs){ return lhs.base() != rhs.base(); }

// template <typename T, typename T1>
// ft::iterator<T> operator!=(ft::iterator<T> &lhs, ft::iterator<T1> &rhs){ return lhs.base() != rhs.base(); }

template <typename T>
bool operator>(const ft::iterator<T> &lhs, const ft::iterator<T> &rhs){ return lhs.base() > rhs.base(); }

template <typename T, typename T1>
bool operator>( const ft::iterator<T> &lhs, const ft::iterator<T1> &rhs){ return lhs.base() > rhs.base(); }

template <typename T>
bool operator>=( const ft::iterator<T> &lhs, const ft::iterator<T> &rhs){ return lhs.base() >= rhs.base(); }

template <typename T, typename T1>
bool operator>=( const ft::iterator<T> &lhs, const ft::iterator<T1> &rhs){ return lhs.base() >= rhs.base(); }

template <typename T>
bool operator<(const ft::iterator<T> &lhs, const ft::iterator<T> &rhs){ return lhs.base() < rhs.base(); }

template <typename T, typename T1>
bool operator<(const ft::iterator<T> &lhs, const ft::iterator<T1> &rhs){ return lhs.base() < rhs.base(); }

template <typename T>
bool operator<=(const ft::iterator<T> &lhs, const ft::iterator<T> &rhs){ return lhs.base() <= rhs.base(); }

template <typename T, typename T1>
bool operator<=(const ft::iterator<T> &lhs, const ft::iterator<T1> &rhs){ return lhs.base() <= rhs.base(); }

template <typename T>
ptrdiff_t operator-(const ft::iterator<T> &lhs,const ft::iterator<T> &rhs){ return lhs.base() - rhs.base(); }

template <typename T, typename T1>
ptrdiff_t operator-(const ft::iterator<T> &lhs, const ft::iterator<T1> &rhs){ return lhs.base() - rhs.base(); }

template <typename T>
ptrdiff_t operator+(const ft::iterator<T> &lhs, const ft::iterator<T> &rhs){ return lhs.base() + rhs.base(); }

template <typename T, typename T1>
ptrdiff_t operator+(const ft::iterator<T> &lhs, const ft::iterator<T1> &rhs){ return lhs.base() + rhs.base(); }

template<typename T> ft::iterator<T> operator+(
         typename ft::iterator<T>::difference_type x,
        const typename ft::iterator<T>& rhs)
    { return (rhs + x); }



template <typename T>
bool operator>(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T> &rhs){ return lhs.base() < rhs.base(); }

template <typename T, typename T1>
bool operator>(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T1> &rhs){ return lhs.base() < rhs.base(); }

template <typename T>
bool operator>=(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T> &rhs){ return lhs.base() <= rhs.base(); }

template <typename T, typename T1>
bool operator>=(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T1> &rhs){ return lhs.base() <= rhs.base(); }

template <typename T>
bool operator<(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T> &rhs){ return lhs.base() > rhs.base(); }

template <typename T, typename T1>
bool operator<(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T1> &rhs){ return lhs.base() > rhs.base(); }

template <typename T>
bool operator<=(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T> &rhs){ return lhs.base() >= rhs.base(); }

template <typename T, typename T1>
bool operator<=(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T1> &rhs){ return lhs.base() >= rhs.base(); }

template <typename T>
ptrdiff_t operator-(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T> &rhs){ return lhs.base() - rhs.base(); }

template <typename T, typename T1>
ptrdiff_t operator-(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T1> &rhs){ return lhs.base() - rhs.base(); }

template <typename T>
ptrdiff_t operator+(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T> &rhs){ return lhs.base() + rhs.base(); }

template <typename T, typename T1>
ptrdiff_t operator+(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T1> &rhs){ return lhs.base() + rhs.base(); }

template<typename T> ft::reverse_iterator<T> operator+(
         typename ft::reverse_iterator<T>::difference_type x,
        const typename ft::reverse_iterator<T>& rhs)
    { return (rhs + x); }

#endif