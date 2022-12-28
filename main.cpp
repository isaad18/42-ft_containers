#include <string>
#include <iostream>
#include <vector>
#include "includes/vector.hpp"

int main(){
	std::vector<int> v;
	std::vector<int> v6;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	v6.push_back(4);
	v6.push_back(5);
	v6.push_back(6);

	for (int i = 0; i < int(v.size()); i++)
		std::cout << v[i] << std::endl;
	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::vector<int>::iterator it = v.begin();
	std::vector<int>::iterator it1 = v.end();
	v.insert(v6.begin(), it, it1);
	// v.insert(it, 66, 122);
	// v6.erase(it, it1);

	// v.assign(v.begin(), v.end());

	// try{
	// 	v.reserve(-2);
	// }
	// catch(std::exception &e){
	// 	std::cout << e.what() << std::endl;
	// }
	// v.insert()
	// std::cout << v.max_size() << std::endl;

	// std::cout << v.capacity() << std::endl;

	// std::cout << v[2] << std::endl;

	for (int i = 0; i < int(v.size()); i++){
		std::cout << v[i] << std::endl;
	}
	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
}