#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "ft.hpp"
#include "iterator.hpp"
#include <exception>
#include <stdexcept>
#include <memory>
#include <cstddef>

namespace ft{
	template <typename T, class Alloc = std::allocator<T> >
	class vector{
		private:
			size_t _size;
			T* data;
			size_t _capacity;

		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef ft::iterator<T> iterator;
			typedef ft::iterator<T const> const_iterator;
			typedef ft::reverse_iterator<T> reverse_iterator;
			typedef ft::reverse_iterator<T const> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;
			Alloc _alloc;
		public:

			vector (const allocator_type& alloc = allocator_type()){
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
			}

			vector(ft::vector<T> &other): _size(0), _capacity(0){
				reserve(other._capacity);
				this->_size = other._size;
				this->_capacity = other._capacity;
				ft::copy(other.data, other.data + other._size, this->data);
			}

			vector (size_t n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n), _capacity(0){
				if (n >= max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				reserve(_size);
				ft::fill(data, data + n, val);
				_size = n;
				_alloc = alloc;
			}

			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()){
			// 	_size = 0;
			// 	_capacity = 0;
			// 	_alloc = alloc;
			// 	assign(first, last);
			// }

			vector(iterator first, iterator last, const allocator_type& alloc = allocator_type()){
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
				assign(first, last);
			}

			vector(const_iterator first, const_iterator last, const allocator_type& alloc = allocator_type()){
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
				assign(first, last);
			}

			void resize(size_t resize){
				if (resize > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				while (resize < _size){
					pop_back();
				}
				if (resize > _size){
					size_t newCapacity = resize;
					if (resize > _capacity * 2) {
						newCapacity = resize + (_capacity / 2);
					}
					else if (resize > _capacity) {
						newCapacity = _capacity * 2;
					}
					reserve(newCapacity);
					ft::fill(data + _size, data + resize, 0);
					_size = resize;
				}
			}

			virtual ~vector(){
				if (_capacity > 0)
					_alloc.deallocate(data, _capacity);
			}

			size_t capacity(){ return _capacity; }

			size_t size(){ return _size; }

			size_t size() const{ return _size; }

			size_t max_size(){ return static_cast<std::size_t>(-1) / sizeof(T); }

			iterator insert( iterator pos, const T& value ){
				size_t index = ft::distance(begin(), pos);
				resize(_size + 1);
				for (size_t i = _size; i > index; i--)
					data[i] = data[i - 1];
				data[index] = value;
				return begin();
			}

			void insert( iterator pos, size_t n, const T& value ){
				size_t index = ft::distance(begin(), pos);
				size_t tmp = index + n;
				resize(_size + n);
				for (size_t i = _size; i > tmp - 1; --i)
					data[i] = data[i - n];
				while (index < tmp){
					data[index] = value;
					index++;
				}
			}

			template <typename it>
			void insert( iterator pos, it first, typename enable_if<!std::is_integral<it>::value,it>::type last ){
				int i = 0;
				iterator tmp1 = first;
				value_type* test = _alloc.allocate(ft::distance(first, last));
				while (tmp1 != last) {
					test[i] = *tmp1;
					i++;
					tmp1++;
				}
				size_t index = ft::distance(begin(), pos);
				size_t dis = ft::distance(first, last);
				size_t tmp = index + (dis);
				resize(_size + (dis));
				for (size_t i = _size - 1; i >= tmp; i--) {
					data[i] = data[i - (dis)];
				}
				i = 0;
				while (index < tmp) {
					data[index] = test[i];
					index++;
					i++;
				}
				_alloc.deallocate(test, ft::distance(first, last));
				return ;
			}

			void reserve(size_t toReserve){
				if (toReserve > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				if (toReserve < _capacity || toReserve == _capacity)
					return ;
				if (_capacity == 0)
					ft::realloc(data, _capacity, toReserve, _capacity, _alloc);
				else
					ft::realloc(data, _capacity, toReserve, _capacity, _alloc);
				_capacity = toReserve;
			}

			template <typename it>
			void assign(it first, typename enable_if<!std::is_integral<it>::value,it>::type last){
				clear();
				reserve(ft::distance(first, last));
				while (first != last){
					_size++;
					data[_size - 1] = *first;
					first++;
				}
			}

			void assign(size_t count, value_type val){
				if (count > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				clear();
				reserve(count);
				resize(count);
				ft::fill(data, data + count, val);
			}

			void clear(){
				_size = 0;
			}

			void resize(size_t newSize, T val) {
				if (newSize > max_size())
					throw std::length_error("vector::resize 'newSize' exceeds maximum supported size");
				if(newSize > _capacity)
					{
						if(newSize > _size*2)
							this->reserve(newSize);
						else
							this->reserve(_size * 2);
					}
				if (newSize > _size) {
					std::fill(data + _size, data + newSize, val);
					_size = newSize;
				} else if (newSize < _size) {
					while (_size > newSize) {
						pop_back();
					}
				} else {
					;
				}
			}

			void	push_back(T const j){
				if (_size == _capacity)
					reserve(_capacity * 2);
				_size++;
				reserve(_size);
				data[_size - 1] = j;
			}

			void swap(ft::vector<value_type> &other){
				ft::swaps(_size, other._size);
				ft::swaps(_capacity, other._capacity);
				ft::swaps(data, other.data);
			}

			iterator erase(iterator pos){
				iterator tmp(pos);
				++tmp;
				return (this->erase(pos, tmp));
			}

			iterator erase(iterator begin, iterator end) {
				if (begin == end)
					return begin;

				// size_t index = ft::distance(this->begin(), begin);
				size_t num_elements = ft::distance(begin, end);
				ft::copy(begin + num_elements, this->end(), begin);
				_size -= num_elements;
				return begin;
			}

			void	pop_back(){
				_size--;
			}

			T &operator[](size_t index){
				return data[index];
			}

			T &operator[](size_t index) const{
				return data[index];
			}

			T &at(size_t index){
				if (index < 0 || index >= _size)
					throw std::out_of_range("vector");
				return data[index];
			}

			iterator begin(){
				return (iterator(&(*data)));
			}

			const_iterator begin() const{
				return (const_iterator(&(*data)));
			}

			iterator end(){
				return (iterator(&(data[this->_size])));
			}

			const_iterator end() const{
				return (const_iterator(&(data[this->_size])));
			}

			reverse_iterator rbegin(void) {
				return (reverse_iterator(&(data[this->_size - 1])));
			}

			const_reverse_iterator rbegin(void) const {
				return (const_reverse_iterator(&(data[this->_size - 1])));
			}

			reverse_iterator rend(void) {
				return (reverse_iterator((data - 1)));
			}

			const_reverse_iterator rend(void) const {
				return (const_reverse_iterator((data - 1)));
			}

			bool empty(){
				return (this->_size == 0);
			}

			T &back(){
				return data[_size - 1];
			}

			T &back() const{
				return data[_size - 1];
			}

			T &front(){
				return data[0];
			}

			T &front() const{
				return data[0];
			}

	};

	// template <class T>
	// bool operator==(const vector<T> &other, const vector<T> &other2){
	// 	if (other.size() != other2.size())
	// 		return false;
	// 	return ft::equal(other.begin(), other.end(), other2.begin());
	// }

	template < class T, class Alloc >
		bool	operator== ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
			if (lhs.size() != rhs.size())
				return (false);
			for (size_t i = 0; i < lhs.size(); i++)
				if (lhs[i] != rhs[i])
					return (false);
			return (true);
		}
	template < class T, class Alloc >
		bool	operator!= ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
			return !(lhs == rhs);
		}
	template < class T, class Alloc >
		bool	operator< ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	template < class T, class Alloc >
		bool	operator<= ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
			return (!(rhs < lhs));
		}
	template < class T, class Alloc >
		bool	operator> ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
			return (rhs < lhs);
		}
	template < class T, class Alloc >
		bool	operator>= ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
			return (!(lhs < rhs));
		}
	template<typename T>
		void swap(vector<T> &x, vector<T> &y) {
			x.swap(y);
		}


}
#endif
