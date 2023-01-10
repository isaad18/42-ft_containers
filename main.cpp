#include <string>
#include <iostream>
#include <vector>
#include "includes/vector.hpp"
#include "includes/map.hpp"

int main(){
	ft::map<int, int> v;
	// ft::map<int, int> v6;

	v.insert(7,7);
	v.insert(66, 66);
	v.insert(77, 77);
	v.insert(88, 88);
	v.insert(99, 99);
	v.insert(10000, 10000);
	v.insert(100, 100);
	v.insert(101, 101);
	// v[66] = 66;
		// std::cout << "hh" << std::endl;
	// v[77] = 77;
	// v[88] = 88;
	// v[99] = 99;
	// v[100] = 100;
	// v[1000] = 1000;
	v[1901] = 1901;
	v[55] = 55;
	v[54] = 54;
	// for (int i = 0; i < 100; i++){
	// 	v[i] = i;
	// }
	// for (int i = 0; i < 50; i++){
	// 	v.deleteit(i);
	// }
	ft::map<int, int>::reverse_iterator it = v.rbegin();
	ft::map<int, int>::reverse_iterator it2 = v.rend();
	// --it2;
	// 	std::cout << it2->first << std::endl;
	for (; it != it2; ++it){
		std::cout << it->first << std::endl;
	}
		// ++it;
		// std::cout << it->first << std::endl;
		// ++it;
		// std::cout << it->first << std::endl;
		// ++it;
		// std::cout << it->first << std::endl;
		// ++it;
		// std::cout << it->first << std::endl;
		// ++it;
		// std::cout << it->first << std::endl;
		// ++it;
		// std::cout << it->first << std::endl;
		// ++it;
		// std::cout << it->first << std::endl;
		// ++it;
		// std::cout << it->first << std::endl;
	// }
		// std::cout << it->first << std::endl;
		// ++it;
		// std::cout << it->first << std::endl;
		// ++it;
		// std::cout << it->first << std::endl;
		// if (it == it2){
		// 	std::cout << "hehheeeee" << std::endl;
		// }
	// v.print2D();
	// v.deleteit(99);
	// v.deleteit(101);
	// v.print2D();
	// v.search(10000);
	// v.deleteAll();

	// v6.push_back(4);
	// v6.push_back(5);
	// v6.push_back(6);

	// for (int i = 0; i < int(v.size()); i++)
	// 	std::cout << v[i] << std::endl;
	// std::cout << "size: " << v.size() << std::endl;
	// std::cout << "capacity: " << v.capacity() << std::endl;
	// ft::vector<int>::reverse_iterator it = v6.rbegin();
	// ft::vector<int>::reverse_iterator it1 = v6.rend();
	// for (; it != it1; it++)
	// 	std::cout << *it << std::endl;
	// v.insert(v.begin() + 1, it1, it);
	// it = v.begin();
	// v.insert(it, 5, 122);
	// it = v.begin();
	// v.insert(it, 5);
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

	// for (int i = 0; i < int(v.size()); i++){
	// 	std::cout << v[i] << std::endl;
	// }
	// std::cout << "size: " << v.size() << std::endl;
	// std::cout << "capacity: " << v.capacity() << std::endl;

	// std::vector<int> const vct(6, 12);
	// std::vector<int>::iterator it = vct.begin();
}
