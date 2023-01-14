#ifndef MAP_REVERSE_ITERATOR_HPP
#define MAP_REVERSE_ITERATOR_HPP

#include "map_iterator.hpp"

namespace ft{
	template <class T, class B>
	class map_reverse_iterator: public vc_iterator<ft::random_access_iterator_tag, T>{
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
			map_reverse_iterator(): ptr(NULL){}
			map_reverse_iterator(T ptr) : ptr(ptr.base()){}
			template<class U>
			map_reverse_iterator(U ptr) : ptr(ptr){}
			template<class U, class B1>
			map_reverse_iterator(const m_iterator<U, B1> &other): ptr(const_cast<T *>(other.base())){}
			template<class U, class B1>
			map_reverse_iterator(const map_reverse_iterator<U, B1> &other): ptr(const_cast<T *>(other.base())){}
			T &operator=(T &other){ ptr = other.base(); return *this; }
			B &operator*(){
				T* tmp = ptr;
				if (tmp->index == 1)
					tmp = tmp->parent;
				else if (tmp->left != nullptr) {
					tmp = tmp->left;
					while (tmp->right != nullptr){
						tmp = tmp->right;
					}
				}
				else {
					if (tmp->parent != nullptr) {
						if (tmp->parent->right == tmp){
							tmp = tmp->parent;
						}
						else if (tmp->parent->left == tmp){
							while (tmp->parent->left == tmp)
								tmp = tmp->parent;
							tmp = tmp->parent;
						}
					}
				}
				return (tmp->all);
			}
			B &operator*() const{
				T* tmp = ptr;
				if (tmp->index == 1)
					tmp = tmp->parent;
				else if (tmp->left != nullptr) {
					tmp = tmp->left;
					while (tmp->right != nullptr){
						tmp = tmp->right;
					}
				}
				else {
					if (tmp->parent != nullptr) {
						if (tmp->parent->right == tmp){
							tmp = tmp->parent;
						}
						else if (tmp->parent->left == tmp){
							while (tmp->parent->left == tmp)
								tmp = tmp->parent;
							tmp = tmp->parent;
						}
					}
				}
				return (tmp->all);
			}
			bool operator==(map_reverse_iterator other) const{ return &(*(this->ptr)) == &(*(other.base())); }
			bool operator!=(map_reverse_iterator other) const{ return &(*(this->ptr)) != &(*(other.base())); }
			bool operator>(map_reverse_iterator other) const{ return &(*(this->ptr)) < &(*(other.base())); }
			bool operator<(map_reverse_iterator other) const{ return &(*(this->ptr)) > &(*(other.base())); }
			T *base() const{ return ptr; }
			T &operator[](difference_type num) {
				return (*(*this + num));
			}
			B *operator->() const {
				T* tmp = ptr;
				if (tmp->index == 1)
					tmp = tmp->parent;
				else if (tmp->left != nullptr) {
					tmp = tmp->left;
					while (tmp->right != nullptr){
						tmp = tmp->right;
					}
				}
				else {
					if (tmp->parent != nullptr) {
						if (tmp->parent->right == tmp){
							tmp = tmp->parent;
						}
						else if (tmp->parent->left == tmp){
							while (tmp->parent->left == tmp)
								tmp = tmp->parent;
							tmp = tmp->parent;
						}
					}
				}
				return &(tmp->all);
			}

			map_reverse_iterator &operator--() {
				if (ptr->index == 2){
					ptr = ptr->last;
				}
				else if (ptr->right != nullptr) {
					ptr = ptr->right;
					while (ptr->left != nullptr){
						ptr = ptr->left;
					}
				}
				else {
					if (ptr->parent != nullptr) {
						if (ptr->parent->left == ptr){
							ptr = ptr->parent;
						}
						else if (ptr->parent->right == ptr){
							while (ptr->parent->right == ptr)
								ptr = ptr->parent;
							ptr = ptr->parent;
						}
					}
				}
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
				}
				else if (ptr->index == 1)
					ptr = ptr->parent;
				else if (ptr->right != nullptr) {
					ptr = ptr->right;
					while (ptr->left != nullptr){
						ptr = ptr->left;
					}
				}
				else {
					if (ptr->parent != nullptr) {
						if (ptr->parent->left == ptr){
							ptr = ptr->parent;
						}
						else if (ptr->parent->right == ptr){
							while (ptr->parent->right == ptr)
								ptr = ptr->parent;
							ptr = ptr->parent;
						}
					}
				}
				return (tmp1);
			}
			map_reverse_iterator operator-(int n) const{
				map_reverse_iterator tmp(ptr);
				for (int i = 0; i < n; i++)
					++tmp.ptr;
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



template <typename T, typename B>
bool operator>(const ft::map_reverse_iterator<T, B> &lhs, const ft::map_reverse_iterator<T, B> &rhs){ return lhs.base() < rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator>(const ft::map_reverse_iterator<T, B> &lhs, const ft::map_reverse_iterator<T1, B1> &rhs){ return lhs.base() < rhs.base(); }

template <typename T, typename B>
bool operator>=(const ft::map_reverse_iterator<T, B> &lhs, const ft::map_reverse_iterator<T, B> &rhs){ return lhs.base() <= rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator>=(const ft::map_reverse_iterator<T, B> &lhs, const ft::map_reverse_iterator<T1, B1> &rhs){ return lhs.base() <= rhs.base(); }

template <typename T, typename B>
bool operator<(const ft::map_reverse_iterator<T, B> &lhs, const ft::map_reverse_iterator<T, B> &rhs){ return lhs.base() > rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator<(const ft::map_reverse_iterator<T, B> &lhs, const ft::map_reverse_iterator<T1, B1> &rhs){ return lhs.base() > rhs.base(); }

template <typename T, typename B>
bool operator<=(const ft::map_reverse_iterator<T, B> &lhs, const ft::map_reverse_iterator<T, B> &rhs){ return lhs.base() >= rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
bool operator<=(const ft::map_reverse_iterator<T, B> &lhs, const ft::map_reverse_iterator<T1, B1> &rhs){ return lhs.base() >= rhs.base(); }

template <typename T, typename T1, typename B, typename B1>
ptrdiff_t operator-(const ft::map_reverse_iterator<T, B> &lhs, const ft::map_reverse_iterator<T1, B1> &rhs){ return (rhs.base() - lhs.base()); }

template <typename T, typename T1, typename B, typename B1>
ptrdiff_t operator+(const ft::map_reverse_iterator<T, B> &lhs, const ft::map_reverse_iterator<T1, B1> &rhs){ return lhs.base() + rhs.base(); }

template<typename T, typename B> ft::map_reverse_iterator<T, B> operator+(typename ft::map_reverse_iterator<T, B>::difference_type x, const typename ft::map_reverse_iterator<T, B>& rhs){ return ft::map_reverse_iterator<T, B>(rhs.base() - x); }

#endif