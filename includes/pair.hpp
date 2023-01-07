#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft{
	template<typename T, typename T1>
	class pair{
		private:
			T _first;
			T1 _second;
			pair(){}
		public:
			pair(T first, T1 second): _first(_first), _second(_second) {}
			pair(const pair &other): _first(other.first), _second(other.second) {}
			pair &operator=(const pair &other){
				setFirst(other.first);
				setSecond(other.second);
			}
			T &first() const{ return _first; }
			T1 &second() const{ return _second; }
			T &first(){ return _first; }
			T1 &second(){ return _second; }
			void setFirst(T first){ _first = first; }
			void setSecond(T second){ _second = second; }
	};

	template<typename T, typename T1>
	pair<T, T1> &make_pair(T first, T second){
		pair<T, T1> p(first, second);
		return p;
	}
}

#endif