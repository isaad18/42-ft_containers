#ifndef M_ITERATOR_HPP

#define M_ITERATOR_HPP

#include <cstring>
#include "ft.hpp"
#include "../containers/map.hpp"
#include "pair.hpp"
#include "iterator_traits.hpp"

namespace ft{

	template <typename T, typename B, class Compare>
	class m_iterator: public vc_iterator<ft::random_access_iterator_tag, T>{
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
			Compare compare;
			m_iterator(): ptr(NULL) {}
			template<class U>
			m_iterator(U ptr) : ptr(ptr){}
			m_iterator(T *ptr) : ptr(ptr){}
			template<class U, class B1, class gerard>
			m_iterator(const m_iterator<U, B1, gerard> &other): ptr((other.base())){}
			T &operator=(T &other){ ptr = other.base(); return *this; }

			B &operator*() const{ return base()->all; }
			bool operator==(const m_iterator other) const{
				return &(*(this->ptr)) == &(*(other.base()));
			}
			bool operator!=(const m_iterator other) const{
				return &(*(this->ptr)) != &(*(other.base()));
			}
			bool operator>(const m_iterator other) const{
				return &(*(this->ptr)) > &(*(other.base()));
			}
			bool operator<(const m_iterator other) const{
				return &(*(this->ptr)) < &(*(other.base()));
			}
			T *base() const{
				return ptr;
			}
			T &operator[](difference_type num) {
				return (*(*this + num));
			}
			B *operator->() const {
				if (ptr == NULL)
					return NULL;
				return &(ptr->all);
			}

			m_iterator &operator++() {
				increment();
				return *this;
			}
			m_iterator &operator--() {
				decrement();
				return *this;
			}

			m_iterator operator--(int){
				m_iterator tmp(ptr);
				decrement();
				return tmp;
			}
			m_iterator operator++(int){
				m_iterator tmp1(ptr);
				increment();
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

			void decrement(){
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

			void increment(){
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

	};

}

#endif
