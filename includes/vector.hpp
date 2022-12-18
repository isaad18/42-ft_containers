#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "ft.hpp"
#include "iterator.hpp"

namespace ft{
	template <typename T>
	class vector{
		private:
			size_t _size;
			T* data;
			size_t _capacity;
		public:
			typedef T value_type;
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

			vector(T n, const T& val): _size(n), _capacity(0){
				reserve(_size);
				ft::fill(data, data + n, val);
				_size = n;
			}

			~vector(){
				if (_capacity > 0)
					delete[] data;
			}

			size_t capacity(){ return _capacity; }

			size_t size(){ return _size; }

			size_t max_size(){ return static_cast<std::size_t>(-1) / sizeof(T); }

			void reserve(size_t toReserve){
				if (toReserve < _capacity)
					return ;
				ft::realloc(data, _capacity, toReserve);
				_capacity = toReserve;
			}

			void resize(size_t resize){
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

			void clear(){
				_size = 0;
			}

			void assign(int count, value_type val){
				if (count < 0)
					throw std::length_error("vector");
				clear();
				reserve(count);
				resize(count);
				ft::fill(data, data + count, val);
			}

			template <typename T1>
			void assign(T1 first, T1 last){
				if (first > last)
					throw std::length_error("vector");
				clear();
				reserve(ft::distance(first, last));
				resize(ft::distance(first, last));
				ft::copy(first, last, this->data);
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

			void resize(size_t resize, T val){
				while (resize < _size){
					pop_back();
				}
				if (resize > _size){
					reserve(resize);
					ft::fill(data + _size, data + resize, val);
					_size = resize;
				}
			}

			void	push_back(T const j){
				if (_size == _capacity)
					reserve(_capacity * 2);
				_size++;
				reserve(_size);
				data[_size - 1] = j;
			}

			void	pop_back(){
				_size--;
			}

			T &operator[](unsigned int index){
				return data[index];
			}

			T &operator[](unsigned int index) const{
				return data[index];
			}

			iterator begin(){
				return (iterator(data));
			}

			const_iterator begin() const{
				return (const_iterator(data));
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