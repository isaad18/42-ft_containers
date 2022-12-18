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

// int main() {
//   ft::vector<int> v1;
//   ft::vector<int> v2;

//   v1.reserve(4);
//   v1.push_back(1);
//   v1.push_back(2);
//   v1.push_back(3);
//   v1.push_back(4);
//   v2.reserve(2);
//   v2.push_back(5);
//   v2.push_back(6);
// 	for (int i = 0; i < int(v1.size()); i++)
// 		std::cout << v1[i] << std::endl;
// 	std::cout << "size " << v1.size() << std::endl;
// 	std::cout << "capacity " << v1.capacity() << std::endl;
// 	for (int i = 0; i < int(v2.size()); i++)
// 		std::cout << v2[i] << std::endl;
// 	std::cout << "size " << v2.size() << std::endl;
// 	std::cout << "capacity " << v2.capacity() << std::endl;

//   v1.swap(v2);

// 	for (int i = 0; i < int(v1.size()); i++)
// 		std::cout << v1[i] << std::endl;
// 	std::cout << "size " << v1.size() << std::endl;
// 	std::cout << "capacity " << v1.capacity() << std::endl;
// 	for (int i = 0; i < int(v2.size()); i++)
// 		std::cout << v2[i] << std::endl;
// 	std::cout << "size " << v2.size() << std::endl;
// 	std::cout << "capacity " << v2.capacity() << std::endl;

//   return 0;
// }