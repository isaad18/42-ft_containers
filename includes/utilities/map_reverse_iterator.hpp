#ifndef MAP_REVERSE_ITERATOR_HPP
#define MAP_REVERSE_ITERATOR_HPP

#include "map_iterator.hpp"

namespace ft{
	template <class T, class B, class Compare>
	class map_reverse_iterator: public vc_iterator<ft::random_access_iterator_tag, T>{
		private:
		public:
			typedef ft::vc_iterator<ft::random_access_iterator_tag, T> iterator_traits;
			typedef typename iterator_traits::difference_type difference_type;
			typedef typename iterator_traits::pointer pointer;
			typedef typename iterator_traits::reference reference;
			typedef typename iterator_traits::value_type value_type;
			typedef typename iterator_traits::iterator_category iterator_category;
		public:
			T *ptr;
			map_reverse_iterator(): ptr(NULL){}
			map_reverse_iterator(T ptr) : ptr(ptr.ptr){}
			template<class U>
			map_reverse_iterator(U ptr) : ptr(ptr){}
			template<class U, class B1, class gerard>
			map_reverse_iterator(const m_iterator<U, B1, gerard> &other): ptr(const_cast<T *>(other.ptr)){}
			template<class U, class B1, class gerard>
			map_reverse_iterator(const map_reverse_iterator<U, B1, gerard> &other): ptr(const_cast<T *>(other.ptr)){}
			T &operator=(T &other){ ptr = other.base(); return *this; }
			B &operator*(){
				T* tmp = ptr;
				if (tmp->index == 1)
					tmp = tmp->parent;
				else if (tmp->left != NULL) {
					tmp = tmp->left;
					while (tmp->right != NULL){
						tmp = tmp->right;
					}
				}
				else {
					if (tmp->parent != NULL) {
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
				else if (tmp->left != NULL) {
					tmp = tmp->left;
					while (tmp->right != NULL){
						tmp = tmp->right;
					}
				}
				else {
					if (tmp->parent != NULL) {
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
			bool operator==(map_reverse_iterator other) const{ return &(*(this->base())) == &(*(other.base())); }
			bool operator!=(map_reverse_iterator other) const{ return &(*(this->base())) != &(*(other.base())); }
			bool operator>(map_reverse_iterator other) const{ return &(*(this->base())) < &(*(other.base())); }
			bool operator<(map_reverse_iterator other) const{ return &(*(this->base())) > &(*(other.base())); }
			m_iterator<T, B, Compare> base() const{ m_iterator<T, B, Compare> other(ptr); return other;}
			T &operator[](difference_type num) {
				return (*(*this + num));
			}
			B *operator->() const {
				T* tmp = ptr;
				if (tmp->index == 1)
					tmp = tmp->parent;
				else if (tmp->left != NULL) {
					tmp = tmp->left;
					while (tmp->right != NULL){
						tmp = tmp->right;
					}
				}
				else {
					if (tmp->parent != NULL) {
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
				decrement_rev();
				return *this;
			}
			map_reverse_iterator &operator++() {
				increment_rev();
				return *this;
			}

			map_reverse_iterator operator++(int){
				map_reverse_iterator tmp(ptr);
				increment_rev();
				return tmp;
			}
			map_reverse_iterator operator--(int){
				map_reverse_iterator tmp1(ptr);
				decrement_rev();
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

			void increment_rev(){
				if (ptr->index == 1)
					ptr = ptr->parent;
				else if (ptr->left != NULL) {
					ptr = ptr->left;
					while (ptr->right != NULL){
						ptr = ptr->right;
					}
				}
				else {
					if (ptr->parent != NULL) {
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
			}

			void decrement_rev(){
				if (ptr->index == 2){
					ptr = ptr->last;
				}
				else if (ptr->index == 1)
					ptr = ptr->parent;
				else if (ptr->right != NULL) {
					ptr = ptr->right;
					while (ptr->left != NULL){
						ptr = ptr->left;
					}
				}
				else {
					if (ptr->parent != NULL) {
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
			}

			void decrement_rev_se(){
				if (ptr->index == 1)
					ptr = ptr->parent;
				else if (ptr->right != NULL) {
					ptr = ptr->right;
					while (ptr->left != NULL){
						ptr = ptr->left;
					}
				}
				else {
					if (ptr->parent != NULL) {
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
			}
	};
}

#endif
