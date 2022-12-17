#ifndef ITERATOR_HPP

#define ITERATOR_HPP

namespace ft{
	template <typename T>
	class iterator{
		private:
			T *ptr;
		public:
			iterator(T *ptr) : ptr(ptr){}
			T &operator*(){ return *ptr; }
			bool &operator==(T const &other){ return *ptr == other; }
			bool &operator!=(T const &other){ return *ptr != other; }
			iterator &operator++(){ ++ptr; return *this; }
	};
}

#endif