#ifndef PAIR_HPP
#define PAIR_HPP

#include <exception>
#include <stdexcept>
#include <memory>
#include <cstddef>

namespace ft{
	template<typename T, typename T1, class Compare = std::less<T> >
	class pair{
		private:
		public:
			T first;
			T1 second;
			pair(){}
			pair(T first, T1 second): first(first), second(second) {}
			pair(const pair &other): first(other.first), second(other.second) {}
			template<typename T2, typename T3>
			pair(const pair<T2, T3> &other): first(static_cast<T>(other.first)), second(static_cast<T1>(other.second)) {}
			pair<T, T1> &operator=(const pair<T, T1> &other){
				first = (other.first);
				second = (other.second);
				return *this;
			}
			void setFirst(T first){ this->first = first; }
			void setSecond(T1 second){ this->second = second; }
	};

	template<typename T, typename T1>
	ft::pair<T, T1, std::less<T> > make_pair(T first, T1 second){
		ft::pair<T, T1, std::less<T> > p(first, second);
		return p;
	}
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first==rhs.first && lhs.second==rhs.second;
	}
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs==rhs);
	}
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	}
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(rhs<lhs);
	}
	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return rhs<lhs;
	}
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs<rhs);
	}


}

#endif
