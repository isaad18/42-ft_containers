#include <string>
#include <iostream>
#include <vector>
#include "includes/vector.hpp"

int main(){
	std::vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	v.assign(-4, 88);

	// try{
	// 	v.reserve(-2);
	// }
	// catch(std::exception &e){
	// 	std::cout << e.what() << std::endl;
	// }
	std::cout << v.max_size() << std::endl;

	std::cout << v.capacity() << std::endl;

	std::cout << v.at(2) << std::endl;

	// for (int i = 0; i < 100; i++)
	// 	std::cout << v[i] << std::endl;
	// std::cout << v.capacity() << std::endl;
}