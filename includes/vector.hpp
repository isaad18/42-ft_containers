#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <exception>
#include <iostream>
#include <string>

namespace ft{
	template <typename T>
	class vector{
		private:
			unsigned int size;
			T* data;
			unsigned int pb;
		public:
			vector(){
				size = 0;
				pb = 0;
			}
			~vector(){
				delete[] data;
			}
			// vector(unsigned int size) : size(size){
			// 	if (size > 0) {
			// 		pb = 0;
			// 		data = new T[size];
			// 	}
			// 	else {	
			// 		throw std::exception();
			// 	}
			// }

			/******* add an element at the end *******/
			void	push_back(T const j){
				size++;
				T *new_data = new T[size];
				for (int i = 0; i < size - 1; i++){
					new_data[i] = data[i];
				}
				new_data[size - 1] = j;
				if (size > 1)
					delete[] data;
				data = new_data;
			}
			/******* add an element at the end *******/
			void	pop_back(){
				if (size > 0){
					size--;
				}
				else{
					throw std::exception();
				}
			}
			T &operator[](unsigned int index){
				if (index >= size)
					throw std::exception();
				return data[index];
			}
	};
}

#endif