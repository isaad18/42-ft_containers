#include <iostream>
#include <vector>
#include "./includes/vector.hpp"

int main(){
	ft::vector<int> v;
	// std::vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	// v.
	std::cout << v[0] << v[1] << v[2] << v[3] << v[4] << std::endl;
	// std::cout << v.size() << std::endl;
	v.pop_back();
	v.pop_back();
	try{
		std::cout << v[0] << v[1] << v[2] << v[3] << v[4] << std::endl;
		// std::cout << v.size() << std::endl;
	}
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}