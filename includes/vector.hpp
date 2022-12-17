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

			void reserve(size_t toReserve){
				if (toReserve <= _capacity)
					return ;
				else{
					ft::realloc(data, _capacity, toReserve);
					_capacity = toReserve;
				}
			}

			void	push_back(T const j){
				if (_size == _capacity)
					reserve((2 * _size));
				_size++;
				reserve(_size);
				data[_size - 1] = j;
			}

			void	pop_back(){
				if (_size > 0){
					_size--;
				}
				else{
					throw std::exception();
				}
			}

			T &operator[](unsigned int index){
				return data[index];
			}

			T &operator[](unsigned int index) const{
				return data[index];
			}

			ft::iterator<T> begin(){
				return ((ft::iterator<T>(data, _size)));
			}

			ft::iterator<T> end(){
				ft::iterator<T> j(data, _size);
				for (size_t i = 0; i < _size; i++)
					++j;
				return (j);
			}
	};
}

#endif