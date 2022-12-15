#include <iostream>
#include <vector>
#include "./includes/vector.hpp"

int main(){
	ft::vector<int> v;


	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	std::cout << v[0] << v[1] << v[2] << v[3] << v[4] << std::endl;
	std::cout << "size " << v.size() << std::endl;
	std::cout << "capacity " << v.capacity() << std::endl;

	v.reserve(10);

	std::cout << v[0] << v[1] << v[2] << v[3] << v[4] << std::endl;
	std::cout << "size " << v.size() << std::endl;
	std::cout << "capacity " << v.capacity() << std::endl;
}