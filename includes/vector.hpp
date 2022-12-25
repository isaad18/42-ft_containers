#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "ft.hpp"
#include "iterator.hpp"
#include <exception>
#include <stdexcept>
#include <memory>
#include <cstddef>

namespace ft{
	template <typename T, class Alloc=std::allocator<T> >
	class vector{
		private:
			size_t _size;
			T* data;
			size_t _capacity;

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
		public:
			typedef T value_type;
			typedef Alloc allocator_type
			typedef ft::iterator<T> iterator;
			typedef ft::iterator<T const> const_iterator;
		public:
			vector(){
				_size = 0;
				_capacity = 0;
			}

			vector(ft::vector<T> &other): _size(0), _capacity(0){
				reserve(other._capacity);
				this->_size = other._size;
				this->_capacity = other._capacity;
				ft::copy(other.data, other.data + other._size, this->data);
			}

			vector(size_t n, const T& val): _size(n), _capacity(0){
				if (n >= max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				reserve(_size);
				ft::fill(data, data + n, val);
				_size = n;
			}

			virtual ~vector(){
				if (_capacity > 0)
					delete[] data;
			}

			size_t capacity(){ return _capacity; }

			size_t size(){ return _size; }

			size_t max_size(){ return static_cast<std::size_t>(-1) / sizeof(T); }

			iterator insert( iterator pos, const T& value ){
				size_t index = ft::distance(begin(), pos) - 1;
				resize(_size + 1);
				for (size_t i = _size; i > index - 1; --i)
					data[i] = data[i - 1];
				data[index] = value;
				return begin();
			}

			iterator insert( iterator pos, size_t n, const T& value ){
				size_t index = ft::distance(begin(), pos) - 1;
				size_t tmp = index + n;
				resize(_size + n);
				for (size_t i = _size; i > tmp - 1; --i)
					data[i] = data[i - n];
				while (index < tmp){
					data[index] = value;
					index++;
				}
				return begin();
			}

			// template< class InputIt >
			// iterator insert( const_iterator pos, InputIt first, InputIt last ){
			// 	size_t index = ft::distance(begin(), pos) - 1;
			// 	size_t dis = ft::distance(first, last);
			// 	size_t tmp = index + dis;
			// 	resize(_size + dis);
			// 	for (size_t i = _size; i > tmp - 1; --i)
			// 		data[i] = data[i - dis];
			// 	while (index < tmp){
			// 		data[index] = *first;
			// 		index++;
			// 		first++;
			// 	}
			// 	return begin();
			// }

			void reserve(size_t toReserve){
				if (toReserve > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				if (toReserve < _capacity || toReserve == _capacity)
					return ;
				if (_capacity == 0)
					data = ft::alloc<value_type>(toReserve);
				else
					ft::realloc(data, _capacity, toReserve, _capacity);
				_capacity = toReserve;
			}

			void assign(const_iterator first, const_iterator last){
				clear();
				reserve(ft::distance(first, last));
				while (first != last){
					_size++;
					data[_size - 1] = *first;
					first++;
				}
			}

			void clear(){
				_size = 0;
			}

			void assign(size_t count, value_type val){
				if (count > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				clear();
				reserve(count);
				resize(count);
				ft::fill(data, data + count, val);
			}

			void assign(iterator first, iterator last){
				clear();
				reserve(ft::distance(first, last));
				while (first != last){
					_size++;
					data[_size - 1] = *first;
					first++;
				}
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
				ft::swap(_size, other._size);
				ft::swap(_capacity, other._capacity);
				ft::swap(data, other.data);
			}

			void erase(iterator pos){
				size_t index = ft::distance(begin(), pos);
				for (size_t i = index - 1; i < _size - 1; i++)
					data[i] = data[i + 1];
				_size--;
			}

			void erase(iterator begin, iterator end){
				size_t index = ft::distance(this->begin(), begin);
				size_t range = ft::distance(begin, end) - 1;
				for (size_t i = index - 1; i < _size - range; i++)
					data[i] = data[i + range];
				_size -= range;
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

			bool empty(){
				return (this->_size == 0);
			}
	};
}

#endif
