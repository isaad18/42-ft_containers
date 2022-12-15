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

			~vector(){
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
	};
}

#endif