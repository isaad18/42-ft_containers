#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft{
	template<typename T, typename T1>
	class pair{
		private:
		public:
			T first;
			T1 second;
			pair(){}
			pair(T first, T1 second): first(first), second(second) {}
			pair(const pair &other): first(other.first), second(other.second) {}
			pair<T, T1> &operator=(const pair<T, T1> &other){
				setFirst(other.first);
				setSecond(other.second);
				return *this;
			}
			// T &first(){ return first; }
			// T first() const{ return first; }
			// T1 &second(){ return second; }
			// T1 second() const{ return second; }
			void setFirst(T first){ this->first = first; }
			void setSecond(T second){ this->second = second; }
	};

	template<typename T, typename T1>
	pair<T, T1> make_pair(T first, T1 second){
		pair<T, T1> p(first, second);
		return p;
	}
}

#endif