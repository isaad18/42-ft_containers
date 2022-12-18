#include <iostream>
#include <vector>
#include "./includes/vector.hpp"

int main(){
	// std::vector<int> d(6, 66);
	ft::vector<int> v;
	// std::vector<int> jj;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	// ft::vector<int>::iterator it = v.end();
	// ft::vector<int>::iterator it2 = v.begin();
	// for (; it2 != it; it2++){
	// 	std::cout << *it2 << std::endl;
	// 	// *it2 = 1;
	// }
	std::cout << "size " << v.size() << std::endl;
	std::cout << "capacity " << v.capacity() << std::endl;

	v.reserve(10);

	for (int i = 0; i < int(v.size()); i++)
		std::cout << v[i] << std::endl;
	std::cout << "size " << v.size() << std::endl;
	std::cout << "capacity " << v.capacity() << std::endl;

	v.resize(15);

	for (int i = 0; i < int(v.size()); i++)
		std::cout << v[i] << std::endl;
	std::cout << "size " << v.size() << std::endl;
	std::cout << "capacity " << v.capacity() << std::endl;
	// v.resize(17, 6);
	// v.assign(5, 88);
	// int arr[] = {1, 8, 3, 4};
	std::cout << "last" << std::endl;
	v.assign(v.begin(), v.end());
	// v.push_back(5);
	for (int i = 0; i < int(v.size()); i++)
		std::cout << v[i] << std::endl;
	std::cout << "size " << v.size() << std::endl;
	std::cout << "capacity " << v.capacity() << std::endl;
	// v.resize(4);
	// v.assign(v.begin(), v.end());
	// for (int i = 0; i < int(v.size()); i++)
	// 	std::cout << v[i] << std::endl;
	// std::cout << "size " << v.size() << std::endl;
	// std::cout << "capacity " << v.capacity() << std::endl;
}