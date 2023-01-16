#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft{
	template <class T, class Container = ft::vector<T> >
	class stack{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
		private:
			container_type	_cont;
		public:
			explicit stack(const container_type& ctnr = container_type()): _cont(ctnr){  }

			stack( const stack& other) : _cont(other._cont) {}

			bool empty() const{
				return _cont.empty();
			}

			~stack() {}

			size_type size() const{
				return _cont.size();
			}

			value_type& top(){
				return _cont.back();
			}

			const value_type& top() const{
				return _cont.back();
			}

			void push (const value_type& val){
				_cont.push_back(val);
			}

			void pop(){
				_cont.pop_back();
			}

			friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
				return lhs._cont == rhs._cont;
			}

			friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
				return lhs._cont != rhs._cont;
			}

			friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
				return lhs._cont < rhs._cont;
			}

			friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
				return lhs._cont <= rhs._cont;
			}

			friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
				return lhs._cont > rhs._cont;
			}

			friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
				return lhs._cont >= rhs._cont;
			}
	};
}

#endif
