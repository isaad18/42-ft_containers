#ifndef MAP_REVERSE_ITERATOR_HPP

#define MAP_REVERSE_ITERATOR_HPP

#include <cstring>
#include "ft.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "iterator_traits.hpp"
#include "map_iterator.hpp"

namespace ft{

	template <typename T, typename B>
	class map_reverse_iterator//: public m_iterator<ft::random_access_iterator_tag, T>{
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
			map_reverse_iterator(): ptr(NULL) {}
			map_reverse_iterator(T ptr) : ptr(ptr){}
			template<class U, class B1>
			map_reverse_iterator(const m_iterator<U, B1> &other): ptr(const_cast<T>(other.base())){}
			template<class U>
			map_reverse_iterator(U ptr) : ptr(ptr){}
			template<class U, class B1>
			map_reverse_iterator(const map_reverse_iterator<U, B1> &other): ptr(const_cast<T>(other.base())){}
			T &operator=(T &other){ ptr = other.base(); return *this; }

			B operator*(){ return (base() - 1)->all; }
			B operator*() const{ return (base() - 1)->all; }
			bool operator==(const map_reverse_iterator &other) const{ return &(*(this->ptr)) == &(*(other.base())); }
			bool operator!=(const map_reverse_iterator &other) const{ return &(*(this->ptr)) != &(*(other.base())); }
			bool operator>(const map_reverse_iterator &other) const{ return &(*(this->ptr)) < &(*(other.base())); }
			bool operator<(const map_reverse_iterator &other) const{ return &(*(this->ptr)) > &(*(other.base())); }
			T base() const{ return ptr; }
			T operator[](ptrdiff_t num) {
				return (*(*this + num));
			}
			B *operator->() const { return &(ptr->all); }
			// B *operator->() { return &(ptr->all); }
			map_reverse_iterator &operator--() {
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

			map_reverse_iterator &operator++() {
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

			map_reverse_iterator operator++(int){
				map_reverse_iterator tmp(ptr);
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
			map_reverse_iterator operator--(int){
				map_reverse_iterator tmp1(ptr);
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

			map_reverse_iterator operator-(int n) const{
				map_reverse_iterator tmp(ptr);
				for (int i = 0; i < n; i++){
					++tmp.ptr;
				}
				return tmp;
			}
			map_reverse_iterator operator+(int n) const{
				map_reverse_iterator tmp(ptr);
				for (int i = 0; i < n; i++)
					--tmp.ptr;
				return tmp;
			}
			map_reverse_iterator &operator-=(int n){
				ptr = ptr + n;
				return *this;
			}
			map_reverse_iterator &operator+=(int n){
				ptr = ptr - n;
				return *this;
			}
	};

}

template <typename T, typename T1>
bool operator>(const ft::map_reverse_iterator<T, T1> &lhs, const ft::map_reverse_iterator<T, T1> &rhs){ return lhs.base() < rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator>(const ft::map_reverse_iterator<T, T1> &lhs, const ft::map_reverse_iterator<B, B1> &rhs){ return lhs.base() < rhs.base(); }

template <typename T, typename T1>
bool operator>=(const ft::map_reverse_iterator<T, T1> &lhs, const ft::map_reverse_iterator<T, T1> &rhs){ return lhs.base() <= rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator>=(const ft::map_reverse_iterator<T, T1> &lhs, const ft::map_reverse_iterator<B, B1> &rhs){ return lhs.base() <= rhs.base(); }

template <typename T, typename T1>
bool operator<(const ft::map_reverse_iterator<T, T1> &lhs, const ft::map_reverse_iterator<T, T1> &rhs){ return lhs.base() > rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator<(const ft::map_reverse_iterator<T, T1> &lhs, const ft::map_reverse_iterator<B, B1> &rhs){ return lhs.base() > rhs.base(); }

template <typename T, typename T1>
bool operator<=(const ft::map_reverse_iterator<T, T1> &lhs, const ft::map_reverse_iterator<T, T1> &rhs){ return lhs.base() >= rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator<=(const ft::map_reverse_iterator<T, T1> &lhs, const ft::map_reverse_iterator<B, B1> &rhs){ return lhs.base() >= rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
ptrdiff_t operator-(const ft::map_reverse_iterator<T, T1> &lhs, const ft::map_reverse_iterator<B, B1> &rhs){ return (rhs.base() - lhs.base()); }

template <typename T, typename T1, typename B, typename B1>
ptrdiff_t operator+(const ft::map_reverse_iterator<T, T1> &lhs, const ft::map_reverse_iterator<B, B1> &rhs){ return lhs.base() + rhs.base(); }

template<typename T, typename T1> ft::map_reverse_iterator<T, T1> operator+(typename ft::map_reverse_iterator<T, T1>::difference_type x, const typename ft::map_reverse_iterator<T, T1>& rhs){ return ft::map_reverse_iterator<T, T1>(rhs.base() - x); }

#endif