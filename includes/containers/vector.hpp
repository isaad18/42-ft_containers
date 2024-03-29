#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../utilities/ft.hpp"
#include "../utilities/iterator.hpp"
#include "../utilities/reverse_iterator.hpp"
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
			typedef ft::iterator<const T> const_iterator;
			typedef ft::reverse_iterator<T> reverse_iterator;
			typedef ft::reverse_iterator<const T> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;
			Alloc _alloc;
		public:

			vector (const allocator_type& alloc = allocator_type()){
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
			}

			vector(const ft::vector<T> &other): _size(0), _capacity(0), _alloc(other._alloc){
				reserve(other._capacity);
				this->_size = other._size;
				for (size_t i = 0; i < other._size; i++){
					_alloc.construct(data + i, other.data[i]);
				}
			}

			vector (size_t n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n), _capacity(0){
				if (n >= max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				reserve(_size);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(data + i, val);
				_size = n;
				_alloc = alloc;
			}

			template <class InputIterator>
			vector(InputIterator first, typename enable_if<!ft::is_integral<InputIterator>::value,InputIterator>::type last, const allocator_type& alloc = allocator_type()){
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
				assign(first, last);
			}

			vector &operator=(const vector &other){
				reserve(other._capacity);
				this->_size = other._size;
				for (size_t i = 0; i < other._size; i++){
					_alloc.construct(data + i, other.data[i]);
				}
				return *this;
			}

			void resize(size_t resize){
				if (resize > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				if (resize == _size)
					return;
				if (resize < _size){
					while (resize < _size){
						pop_back();
					}
				}
				else if (resize > _size){
					size_t newCapacity = resize;
					if (resize > _capacity * 2) {
						newCapacity = resize + (_capacity / 2);
					}
					else if (resize > _capacity) {
						newCapacity = _capacity * 2;
					}
					reserve(newCapacity);
					_size = resize;
				}
			}

			virtual ~vector(){
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(data + i);
				if (_capacity > 0)
					_alloc.deallocate(data, _capacity);
			}

			size_t capacity() const{ return _capacity; }

			size_t size() const{ return _size; }

			size_t max_size() const{ return static_cast<std::size_t>(-1) / sizeof(T); }

			iterator insert( iterator pos, const T& value ){
				if (_size == 0 && pos == begin() && pos == end()){
					reserve(2);
					push_back(value);
					return begin();
				}
				size_t index = ft::distance(begin(), pos);
				resize(_size + 1);
				for (size_t i = _size; i > index; i--){
					_alloc.construct(data + i, data[i - 1]);
					_alloc.destroy(data + i - 1);
				}
				_alloc.construct(data + index, value);
				return begin() + index;
			}

			void insert( iterator pos, size_t n, const T& value ){
				size_t index = ft::distance(begin(), pos);
				size_t tmp = index + n;
				resize(_size + n);
				for (size_t i = _size; i > tmp - 1; --i){
					_alloc.construct(data + i, data[i - n]);
					_alloc.destroy(data + i - n);
				}
				while (index < tmp){
					_alloc.construct(data + index, value);
					index++;
				}
			}

			template <typename it>
			void insert( iterator pos, it first, typename enable_if<!ft::is_integral<it>::value,it>::type last ){
				int i = 0;
				it tmp1 = first;
				value_type* test = _alloc.allocate(ft::distance(first, last));
				while (tmp1 != last) {
					_alloc.construct(test + i, *tmp1);
					i++;
					tmp1++;
				}
				size_t index = ft::distance(begin(), pos);
				size_t dis = ft::distance(first, last);
				size_t tmp = index + (dis);
				resize(_size + (dis));
				for (size_t i = _size - 1; i >= tmp; i--) {
					_alloc.construct(data + i, data[i - dis]);
					_alloc.destroy(data + i - dis);
				}
				i = 0;
				while (index < tmp) {
					_alloc.construct(data + index, test[i]);
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
				if (_capacity == 0 && toReserve > 0)
					data = _alloc.allocate(toReserve);
				else
					ft::realloc(data, _capacity, toReserve, _capacity, _alloc);
				_capacity = toReserve;
			}

			template <typename it>
			void assign(it first, typename enable_if<!ft::is_integral<it>::value,it>::type last){
				clear();
				reserve(ft::distance(first, last));
				while (first != last){
					_size++;
					_alloc.construct(data + _size - 1, *first);
					first++;
				}
			}

			void assign(size_t count, value_type val){
				if (count > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				clear();
				reserve(count);
				resize(count);
				for (size_t i = 0; i < count; i++)
					_alloc.construct(data + i, val);
			}

			void clear(){
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(data + i);
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
					for (size_t i = _size; i < newSize; i++)
						_alloc.construct(data + i, val);
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
				_alloc.construct(data + _size - 1, j);
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
				size_t num_elements = ft::distance(begin, end);
				size_t index = ft::distance(this->begin(), begin);
				for (size_t i = index; i < _size - num_elements; i++) {
					_alloc.destroy(data + i);
					_alloc.construct(data + i, data[i + num_elements]);
				}
				_size -= num_elements;
				return begin;
			}

			void	pop_back(){
				if (_size == 0)
					return ;
				_alloc.destroy(data + _size - 1);
				_size--;
			}

			T &operator[](size_t index){
				return data[index];
			}

			T &operator[](size_t index) const{
				return data[index];
			}

			T &at(size_t index) const{
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
				return (reverse_iterator(iterator(&(data[this->_size]))));
			}

			const_reverse_iterator rbegin(void) const {
				return (const_reverse_iterator(const_iterator(&(data[this->_size]))));
			}

			reverse_iterator rend(void) {
				return (reverse_iterator(iterator(&(*data))));
			}

			const_reverse_iterator rend(void) const {
				return (const_reverse_iterator(const_iterator(&(*data))));
			}

			bool empty() const{
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
