#ifndef M_ITERATOR_HPP

#define M_ITERATOR_HPP

#include <cstring>
#include "ft.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "iterator_traits.hpp"

namespace ft{

	template <typename T, typename B>
	class m_iterator//: public m_iterator<ft::random_access_iterator_tag, T>{
		{private:
			T ptr;
		// public:
		// 	typedef ft::m_iterator<ft::random_access_iterator_tag, T> iterator_traits;
		// 	typedef typename iterator_traits::difference_type difference_type;
		// 	typedef typename iterator_traits::pointer pointer;
		// 	typedef typename iterator_traits::reference reference;
		// 	typedef typename iterator_traits::value_type value_type;
		// 	typedef typename iterator_traits::m_iterator_category m_iterator_category;
		public:
			m_iterator(): ptr(NULL) {}
			m_iterator(T ptr) : ptr(ptr){}
			template<class U, class B1>
			m_iterator(const m_iterator<U, B1> &other): ptr(const_cast<T>(other.base())){}
			T &operator=(T &other){ ptr = other.base(); return *this; }

			B operator*(){ return (base()->all); }
			B operator*() const{ return base()->all; }
			bool operator==(const m_iterator &other) const{ return &(*(this->ptr)) == &(*(other.base())); }
			bool operator!=(const m_iterator &other) const{ return &(*(this->ptr)) != &(*(other.base())); }
			bool operator>(const m_iterator &other) const{ return &(*(this->ptr)) > &(*(other.base())); }
			bool operator<(const m_iterator &other) const{ return &(*(this->ptr)) < &(*(other.base())); }
			T base() const{ return ptr; }
			T operator[](ptrdiff_t num) {
				return (*(ptr + num));
			}
			B *operator->() const { return &(ptr->all); }
			// B *operator->() { return &(ptr->all); }
			m_iterator &operator++() {
				if (ptr->index == 2){
					ptr = ptr->last;
					return *this;
				}
				bool ok = false;
				if (ptr->right != nullptr) {
					ok = true;
					ptr = ptr->right;
					while (ptr->left != nullptr){
						ptr = ptr->left;
					}
				}
				else {
					if (ptr->parent != nullptr) {
						if (ptr->parent->left == ptr){
							ok = true;
							ptr = ptr->parent;
						}
						else if (ptr->parent->right == ptr && ptr->parent->parent != nullptr){
							ok = true;
							ptr = ptr->parent->parent;
						}
					}
				}
				if (!ok)
					ptr = ptr->right;
				return *this;
			}
			m_iterator &operator--() {
				if (ptr->index == 1)
					ptr = ptr->parent;
				else if (ptr->left != nullptr) {
					ptr = ptr->left;
					while (ptr->right != nullptr){
						ptr = ptr->right;
					}
				}
				else {
					if (ptr->parent != nullptr) {
						if (ptr->parent->right == ptr){
							ptr = ptr->parent;
						}
						else if (ptr->parent->left == ptr){
							while (ptr->parent->left == ptr)
								ptr = ptr->parent;
							ptr = ptr->parent;
						}
					}
				}
				return *this;
			}

			m_iterator operator--(int){
				m_iterator tmp(ptr);
				if (ptr->index == 1)
					ptr = ptr->parent;
				else if (ptr->left != nullptr) {
					ptr = ptr->left;
					while (ptr->right != nullptr){
						ptr = ptr->right;
					}
				}
				else {
					if (ptr->parent != nullptr) {
						if (ptr->parent->right == ptr){
							ptr = ptr->parent;
						}
						else if (ptr->parent->left == ptr){
							while (ptr->parent->left == ptr)
								ptr = ptr->parent;
							ptr = ptr->parent;
						}
					}
				}
				return tmp;
			}
			m_iterator operator++(int){
				m_iterator tmp1(ptr);
				if (ptr->index == 2){
					ptr = ptr->last;
					return tmp1;
				}
				bool ok = false;
				if (ptr->right != nullptr) {
					ok = true;
					ptr = ptr->right;
					while (ptr->left != nullptr){
						ptr = ptr->left;
					}
				}
				else {
					if (ptr->parent != nullptr) {
						if (ptr->parent->left == ptr){
							ok = true;
							ptr = ptr->parent;
						}
						else if (ptr->parent->right == ptr){
							while (ptr->parent->right == ptr)
								ptr = ptr->parent;
							ptr = ptr->parent;
						}
					}
				}
				if (!ok)
					ptr = ptr->right;
				return (tmp1);
			}
			m_iterator operator+(int n) const{
				m_iterator tmp(ptr);
				for (int i = 0; i < n; i++)
					++tmp.ptr;
				return tmp;
			}
			m_iterator operator-(int n) const{
				m_iterator tmp(ptr);
				for (int i = 0; i < n; i++)
					--tmp.ptr;
				return tmp;
			}
			m_iterator &operator+=(int n){
				ptr = ptr + n;
				return *this;
			}
			m_iterator &operator-=(int n){
				ptr = ptr - n;
				return *this;
			}
	};

}

template <typename T, typename B>
bool operator==(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T, B> &rhs){ return lhs.base() == rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator==(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T1, B1> &rhs){ return lhs.base() == rhs.base(); }

template <typename T, typename B>
bool operator!=(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T, B> &rhs){ return lhs.base() != rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator!=(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T1, B1> &rhs){ return lhs.base() != rhs.base(); }

template <typename T, typename B>
bool operator>(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T, B> &rhs){ return lhs.base() > rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator>( const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T1, B1> &rhs){ return lhs.base() > rhs.base(); }

template <typename T, typename B>
bool operator>=( const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T, B> &rhs){ return lhs.base() >= rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator>=( const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T1, B1> &rhs){ return lhs.base() >= rhs.base(); }

template <typename T, typename B>
bool operator<(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T, B> &rhs){ return lhs.base() < rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator<(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T1, B1> &rhs){ return lhs.base() < rhs.base(); }

template <typename T, typename B>
bool operator<=(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T, B> &rhs){ return lhs.base() <= rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator<=(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T1, B1> &rhs){ return lhs.base() <= rhs.base(); }

template <typename T, typename B>
ptrdiff_t operator-(const ft::m_iterator<T, B> &lhs,const ft::m_iterator<T, B> &rhs){ return lhs.base() - rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
ptrdiff_t operator-(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T1, B1> &rhs){ return lhs.base() - rhs.base(); }

template <typename T, typename B>
ptrdiff_t operator+(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T, B> &rhs){ return lhs.base() + rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
ptrdiff_t operator+(const ft::m_iterator<T, B> &lhs, const ft::m_iterator<T1, B1> &rhs){ return lhs.base() + rhs.base(); }

template<typename T, typename B> ft::m_iterator<T, B> operator+(
		 typename ft::m_iterator<T, B>::difference_type x,
		const typename ft::m_iterator<T, B>& rhs)
	{ return (rhs + x); }

#endif