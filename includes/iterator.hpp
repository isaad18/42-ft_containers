#ifndef iterator_HPP

#define iterator_HPP

#include <cstring>
#include "ft.hpp"
#include "iterator_traits.hpp"

namespace ft{

	template <typename T>
	class iterator: public vc_iterator<ft::random_access_iterator_tag, T>{
		private:
			T *ptr;
		public:
			typedef ft::vc_iterator<ft::random_access_iterator_tag, T> iterator_traits;
			typedef typename iterator_traits::difference_type difference_type;
			typedef typename iterator_traits::pointer pointer;
			typedef typename iterator_traits::reference reference;
			typedef typename iterator_traits::value_type value_type;
			typedef typename iterator_traits::iterator_category iterator_category;
		public:
			iterator(): ptr(NULL) {}
			iterator(T *ptr) : ptr(ptr){}
			template<class U>
			iterator(const iterator<U> &other): ptr((other.base())){}
			T &operator=(T &other){ ptr = other.base(); return *this; }

			T &operator*(){ return *base(); }
			T &operator*() const{ return *base(); }
			bool operator==(const iterator &other) const{ return &(*(this->ptr)) == &(*(other.base())); }
			bool operator!=(const iterator &other) const{ return &(*(this->ptr)) != &(*(other.base())); }
			bool operator>(const iterator &other) const{ return &(*(this->ptr)) > &(*(other.base())); }
			bool operator<(const iterator &other) const{ return &(*(this->ptr)) < &(*(other.base())); }
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
	class reverse_iterator: public vc_iterator<ft::random_access_iterator_tag, T>{
		private:
			T *ptr;
		public:
			typedef ft::vc_iterator<ft::random_access_iterator_tag, T> iterator_traits;
			typedef typename iterator_traits::difference_type difference_type;
			typedef typename iterator_traits::pointer pointer;
			typedef typename iterator_traits::reference reference;
			typedef typename iterator_traits::value_type value_type;
			typedef typename iterator_traits::iterator_category iterator_category;
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
			T &operator*() const{
				return (*(ptr - 1));
			}
			bool operator==(reverse_iterator other) const{ return &(*(this->ptr)) == &(*(other.base())); }
			bool operator!=(reverse_iterator other) const{ return &(*(this->ptr)) != &(*(other.base())); }
			bool operator>(reverse_iterator other) const{ return &(*(this->ptr)) < &(*(other.base())); }
			bool operator<(reverse_iterator other) const{ return &(*(this->ptr)) > &(*(other.base())); }
			T *base() const{ return ptr; }
			T &operator[](difference_type num) {
				return (*(*this + num));
			}
			T *operator->() const { return (&operator*()); }
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
			reverse_iterator operator+(difference_type n) const{
				return reverse_iterator(ptr - n);
			}
			reverse_iterator operator-(difference_type n) const{
				return reverse_iterator(ptr + n);
			}
			reverse_iterator &operator+=(difference_type n){
				ptr -= n;
				return *this;
			}
			reverse_iterator &operator-=(difference_type n){
				ptr += n;
				return *this;
			}
	};

}

template <typename T>
bool operator==(const ft::iterator<T> &lhs, const ft::iterator<T> &rhs){ return lhs.base() == rhs.base(); }

template <typename T, typename T1>
bool operator==(const ft::iterator<T> &lhs, const ft::iterator<T1> &rhs){ return lhs.base() == rhs.base(); }

template <typename T>
bool operator!=(const ft::iterator<T> &lhs, const ft::iterator<T> &rhs){ return lhs.base() != rhs.base(); }

template <typename T, typename T1>
bool operator!=(const ft::iterator<T> &lhs, const ft::iterator<T1> &rhs){ return lhs.base() != rhs.base(); }

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

// template <typename T>
// ptrdiff_t operator-(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T> &rhs){ return lhs.base() - rhs.base(); }

template <typename T, typename T1>
ptrdiff_t operator-(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T1> &rhs){ return (rhs.base() - lhs.base()); }

// template <typename T>
// ptrdiff_t operator+(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T> &rhs){ return lhs.base() + rhs.base(); }

template <typename T, typename T1>
ptrdiff_t operator+(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<T1> &rhs){ return lhs.base() + rhs.base(); }

template<typename T> ft::reverse_iterator<T> operator+(
		 typename ft::reverse_iterator<T>::difference_type x,
		const typename ft::reverse_iterator<T>& rhs)
	{ return ft::reverse_iterator<T>(rhs.base() - x); }

#endif