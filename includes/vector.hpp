#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "general.hpp"

namespace ft{
	template <typename T>
	class vector{
		private:
			size_t _size;
			T* data;
			size_t _capacity;
		public:
			vector(){
				_size = 0;
				_capacity = 0;
			}

			vector(ft::vector<T> &other): _size(0), _capacity(0){
				reserve(other._capacity);
				this->_size = other._size;
				this->_capacity = other._capacity;
				std::copy(other.data, other.data + other._size, this->data);
			}

			vector(T n, const T& val): _size(n), _capacity(0){
				reserve(_size);
				std::fill(data, data + n, val);
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
					_reallocate(data, _capacity, toReserve);
					_capacity = toReserve;
				}
			}

			void	push_back(T const j){
				_size++;
				if (_size <= _capacity)
					reserve(_size);
				else
					reserve(_size + ((2 * _size) / 5));
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
	};
}

#endif