#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft{
	template <class T, class Container = vector<T> >
	class stack{
		public:
			typename T			value_type;
			typename Container	container_type;
			typename size_t		size_type;
		private:
			container_type	_cont;
		public:
			explicit stack(const container_type& ctnr = container_type()){}
	};
}

#endif
