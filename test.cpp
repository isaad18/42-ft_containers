#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include "./includes/containers/vector.hpp"
#include "./includes/containers/map.hpp"
#include "./includes/containers/stack.hpp"

void testIterators(ft::vector<int> &ft_vec, std::vector<int> &std_vec) {
	ft::vector<int>::iterator ft_iter = ft_vec.begin();
	std::vector<int>::iterator std_iter = std_vec.begin();
	while (ft_iter != ft_vec.end() && std_iter != std_vec.end()) {
		if (*ft_iter != *std_iter) {
			std::cout << "❌KO" << std::endl;
			return;
		}
		ft_iter++;
		std_iter++;
	}
	std::cout << "✅OK" << std::endl;

	ft::vector<int>::reverse_iterator ft_riter = ft_vec.rbegin();
	std::vector<int>::reverse_iterator std_riter = std_vec.rbegin();
	while (ft_riter != ft_vec.rend() && std_riter != std_vec.rend()) {
		if (*ft_riter != *std_riter) {
			std::cout << "❌KO" << std::endl;
			return;
		}
		ft_riter++;
		std_riter++;
	}
	std::cout << "✅OK" << std::endl;
}

void push_rand1000(ft::vector<int> &ft_vec, std::vector<int> &std_vec) {
	for (int i = 0; i < 1000; i++) {
		int tmp = rand();
		ft_vec.push_back(tmp);
		std_vec.push_back(tmp);
	}
}

void testMap(ft::map<std::string, std::string> ft_map, std::map<std::string, std::string> std_map) {
	// Insert elements into the maps
	ft_map["first"] = "First";
	ft_map["second"] = "Second";
	ft_map["third"] = "Third";
	ft_map["fourth"] = "Fourth";
	ft_map["fifth"] = "Fifth";
	std_map["first"] = "First";
	std_map["second"] = "Second";
	std_map["third"] = "Third";
	std_map["fourth"] = "Fourth";
	std_map["fifth"] = "Fifth";

	// Test for size
	if (ft_map.size() != std_map.size()) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for empty
	if (ft_map.empty() != std_map.empty()) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for count
	if (ft_map.count("first") != std_map.count("first")) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for find
	if (ft_map.find("first")->second != std_map.find("first")->second) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for operator[]
	if (ft_map["first"] != std_map["first"]) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for at()
	try {
		if (ft_map.at("first") != std_map.at("first")) {
			std::cout << "❌KO" << std::endl;
			return;
		}
	} catch (std::out_of_range &e) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for begin and end iterators
	ft::map<std::string, std::string>::iterator ft_iter = ft_map.begin();
	std::map<std::string, std::string>::iterator std_iter = std_map.begin();
	while (ft_iter != ft_map.end() && std_iter!= std_map.end()) {
	if (ft_iter->first != std_iter->first || ft_iter->second != std_iter->second) {
	std::cout << "❌KO" << std::endl;
	return;
	}
	ft_iter++;
	std_iter++;
	}
	std::cout << "✅OK" << std::endl;
	// Test for rbegin and rend iterators
ft::map<std::string, std::string>::reverse_iterator ft_riter = ft_map.rbegin();
std::map<std::string, std::string>::reverse_iterator std_riter = std_map.rbegin();
while (ft_riter != ft_map.rend() && std_riter != std_map.rend()) {
	if (ft_riter->first != std_riter->first || ft_riter->second != std_riter->second) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	ft_riter++;
	std_riter++;
	}
	std::cout << "✅OK" << std::endl;

	ft_map.erase(std::string("first"));
	std_map.erase(std::string("first"));
	if (ft_map.size() != std_map.size()) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for clear
	ft_map.clear();
	std_map.clear();
	if (ft_map.empty() != std_map.empty()) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;
}

void bounds(){
	ft::map<std::string, std::string> ft_map;
	std::map<std::string, std::string> std_map;
	ft_map["first"] = "First";
	ft_map["third"] = "Third";
	ft_map["fourth"] = "Fourth";
	std_map["first"] = "First";
	std_map["third"] = "Third";
	std_map["fourth"] = "Fourth";
	ft::map<std::string, std::string>::iterator lb = ft_map.lower_bound("h");
	std::map<std::string, std::string>::iterator lb_std = std_map.lower_bound("h");
	ft::map<std::string, std::string>::iterator ub = ft_map.upper_bound("second");
	std::map<std::string, std::string>::iterator ub_std = std_map.upper_bound("second");
	if(lb->first != lb_std->first || lb->second != lb_std->second || ub->first != ub_std->first || ub->second != ub_std->second) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;
}

void testVector(){
	ft::vector<int> ft_vec;
	std::vector<int> std_vec;

	push_rand1000(ft_vec, std_vec);

	ft_vec.push_back(1);
	std_vec.push_back(1);
	if (ft_vec[0] == std_vec[0]) {
		std::cout << "✅OK" << std::endl;
	} else {
		std::cout << "❌KO" << std::endl;
	}

	ft_vec.pop_back();
	std_vec.pop_back();
	if (ft_vec.empty() && std_vec.empty()) {
		std::cout << "❌KO" << std::endl;
	} else {
		std::cout << "✅OK" << std::endl;
	}

	ft_vec.insert(ft_vec.begin(), 10);
	std_vec.insert(std_vec.begin(), 10);
	if (ft_vec.size() == std_vec.size()) {
		std::cout << "✅OK" << std::endl;
	} else {
		std::cout << "❌KO" << std::endl;
	}

	ft_vec.erase(ft_vec.begin());
	std_vec.erase(std_vec.begin());
	if (ft_vec.front() == std_vec.front()) {
		std::cout << "✅OK" << std::endl;
	} else {
		std::cout << "❌KO" << std::endl;
	}

	ft_vec.clear();
	std_vec.clear();
	if (ft_vec.empty() && std_vec.empty()) {
		std::cout << "✅OK" << std::endl;
	} else {
		std::cout << "❌KO" << std::endl;
	}

	push_rand1000(ft_vec, std_vec);

	ft::vector<int> ft_vec_1;
	std::vector<int> std_vec_1;

	push_rand1000(ft_vec_1, std_vec_1);

	ft::vector<int> ft_vec_2;
	std::vector<int> std_vec_2;

	push_rand1000(ft_vec_2, std_vec_2);

	ft::vector<ft::vector<int> > ft_vec2;
	std::vector<std::vector<int> > std_vec2;

	ft_vec2.push_back(ft_vec);
	ft_vec2.push_back(ft_vec_1);
	ft_vec2.push_back(ft_vec_2);

	std_vec2.push_back(std_vec);
	std_vec2.push_back(std_vec_1);
	std_vec2.push_back(std_vec_2);

	if (ft_vec2[0][0] == std_vec2[0][0]) {
		std::cout << "✅OK" << std::endl;
	} else {
		std::cout << "❌KO" << std::endl;
	}

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 1000; i++) {
			if (ft_vec2[j][i] != std_vec2[j][i]) {
				std::cout << "❌KO" << std::endl;
				return ;
			}
		}
	}
	std::cout << "✅OK " << std::endl;

	testIterators(ft_vec, std_vec);
}

void testStack(ft::stack<int> &ft_stack, std::stack<int> &std_stack) {
	// Push elements into the stacks
	for (int i = 0; i < 5; i++) {
		ft_stack.push(i);
		std_stack.push(i);
	}

	// Test for size
	if (ft_stack.size() != std_stack.size()) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for empty
	if (ft_stack.empty() != std_stack.empty()) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for top
	if (ft_stack.top() != std_stack.top()) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for pop
	ft_stack.pop();
	std_stack.pop();

	if (ft_stack.top() != std_stack.top()) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;

	// Test for swap
	ft::stack<int> ft_stack_temp;
	std::stack<int> std_stack_temp;
	// ft_stack_temp.swap(ft_stack);
	// std_stack_temp.swap(std_stack);
	if (ft_stack_temp.size() != std_stack_temp.size()) {
		std::cout << "❌KO" << std::endl;
		return;
	}
	std::cout << "✅OK" << std::endl;
}



// int main() {

// 	std::cout << "____________________VECTOR TEST____________________" << std::endl;
// 	testVector();

// 	std::cout << "____________________MAP TEST____________________" << std::endl;
// 	ft::map<std::string, std::string> ft_map;
// 	std::map<std::string, std::string> std_map;
// 	testMap(ft_map, std_map);
// 	bounds();
// 	std::cout << "____________________STACK TEST____________________" << std::endl;
// 	ft::stack<int> ft_stack;
// 	std::stack<int> std_stack;
// 	testStack(ft_stack, std_stack);

	// ft::map<int, int> test;
	// // std::map<int, int> test;

	// std::cout << "test" << std::endl;
	// for (size_t i = 0; i < 25; i++){
	// 	test[i] = i;
	// }
	// ft::map<int, int>::iterator it = test.begin();
	// ft::map<int, int>::iterator it2 = test.end();
	// // test.insert(ft::make_pair(1, 1));
	// // test.insert(ft::make_pair(1, 2));
	// // test.print2D();
	// // std::cout << "testVector" << std::endl;
	// // for (size_t i = 0; i < 100000000; i++){
	// // 	testVector.push_back(i);
	// // }
	// test.erase(3);
	// // test.erase(5);
	// for (; it != it2; it++){
	// 	std::cout << it->first << std::endl;
	// }

// 	return 0;
// }

#define INSERT_BY_PAIR         1
#define INSERT_BY_MAKE_PAIR    2
#define INSERT_BY_OPERATOR     3

template <typename key, typename value>
void insertValue(ft::map<key, value> &map, int insert_style,
                 typename ft::map<key, value>::key_type first,
                 typename ft::map<key, value>::mapped_type second) {
	if (insert_style == INSERT_BY_PAIR) {
		map.insert(ft::pair<key, value>(first, second));
	} else if (insert_style == INSERT_BY_MAKE_PAIR) {
		map.insert(ft::make_pair(first, second));
	} else if (insert_style == INSERT_BY_OPERATOR) {
		map[first] = second;
	} else {
		throw std::out_of_range("Incorrect insert style");
	}
}

// template <typename key, typename value>
// void printMapInfo(ft::map<key, value> &map) {
// 	std::cout << "--------------------------------------------------" << std::endl
// 	          << "map::empty() = " << std::boolalpha << map.empty() << std::endl
// 	          << "map::size() = " << map.size() << std::endl
// 	          << "Contents:" << std::endl;
// }

template <typename key, typename value>
void printContent(ft::map<key, value> &map) {
	printMapInfo(map);
	for (typename ft::map<key, value>::iterator it = map.begin(); it != map.end(); it++) {
		std::cout << "Key = " << it->first << "   |   Value = " << it->second << std::endl;
	}
	std::cout << std::endl;
}

// template <typename key, typename value>
// void insertValue(ft::map<key, value> &map,
//                  typename ft::map<key, value>::iterator position,
//                  typename ft::map<key, value>::key_type first,
//                  typename ft::map<key, value>::mapped_type second) {
// 	map.insert(position, ft::make_pair(first, second));
// }

template <typename key, typename value>
void insertValue(ft::map<key, value> &map,
                 typename ft::map<key, value>::iterator position,
                 typename ft::map<key, value>::key_type first,
                 typename ft::map<key, value>::mapped_type second) {
	map.insert(position, ft::make_pair(first, second));
}

template <typename key, typename value>
void insertRandomValues(ft::map<key, value> &map, size_t size) {
	for (size_t i = 0; i < size; i++) {
		insertValue(map, 1 + (std::rand() % 3), 10000 + (std::rand() % 20000), 10000 + (std::rand() % 30000));
	}
}

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sys/time.h>
#include <map>

// int main() {
// 	timeval exec_time;
// 	gettimeofday(&exec_time, NULL);
// 	double start = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;

// 	ft::map<int, int> test;
// 	insertRandomValues(test, 30);
// 	printContent(test);
	
// 	ft::map<int, int> clone(test);
// 	printContent(clone);

// 	clone.erase(1234);
// 	clone.erase(2339);
// 	clone.erase(9876);
// 	clone.erase(3919);
// 	printContent(clone);

// 	clone.erase(clone.begin(), clone.begin());
// 	clone.erase(clone.end(), clone.end());
// 	printContent(clone);

// 	clone.swap(test);
// 	printContent(test);
// 	printContent(clone);

// 	clone.erase(++(++(clone.begin())));
// 	clone.erase(++(clone.begin()));
// 	clone.erase(--clone.end());
// 	printContent(clone);

// 	clone.erase(++(++clone.begin()), clone.end());
// 	printContent(clone);

// 	test.erase(test.begin(), test.end());
// 	printContent(test);

// 	gettimeofday(&exec_time, NULL);
// 	double end = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;
// 	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
// 	return 0;
// }

template <typename key1, typename key2, typename value>
void printMapOfMaps(ft::map<key1, ft::map<key2, value> > &map);

template <typename key, typename value>
void printMapInfo(ft::map<key, value> &map) {
	std::cout << "--------------------------------------------------" << std::endl
	          << "map::empty() = " << std::boolalpha << map.empty() << std::endl
	          << "map::size() = " << map.size() << std::endl
	          << "Contents:" << std::endl;
}

int main() {
	timeval exec_time;
	gettimeofday(&exec_time, NULL);
	double start = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;

	ft::map<std::string, ft::map<int, int> > test;
	ft::map<int, int> value_for_test[5];

	insertRandomValues(value_for_test[0], 5);
	insertRandomValues(value_for_test[1], 10);
	insertRandomValues(value_for_test[2], 15);
	insertRandomValues(value_for_test[3], 20);
	insertRandomValues(value_for_test[4], 25);

	test.insert(ft::make_pair("Lorem ipsum dolor sit amet.", value_for_test[0]));
	test.insert(ft::make_pair("🚀🚀🚀", value_for_test[1]));
	test.insert(ft::make_pair("Why am I doing this 😭", value_for_test[2]));
	test.insert(ft::make_pair("42 Abu Dhabi", value_for_test[3]));
	test.insert(ft::make_pair("The quick brown fox jumps over the lazy dog", value_for_test[4]));
	printMapOfMaps(test);

	ft::map<std::string, ft::map<int, int> > clone = test;
	clone.erase(clone.begin());
	clone.erase(++clone.begin());
	clone.insert(ft::make_pair("It's fascinating that you know all the planets.", value_for_test[4]));
	clone.insert(ft::make_pair("I admire your courage but I don't admire your singing ability.", value_for_test[2]));
	printMapOfMaps(clone);

	test.swap(clone);
	printMapOfMaps(test);
	printMapOfMaps(clone);

	clone.erase(clone.begin(), clone.end());
	test.clear();

	gettimeofday(&exec_time, NULL);
	double end = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}

template <typename key1, typename key2, typename value>
void printMapOfMaps(ft::map<key1, ft::map<key2, value> > &map) {
	printMapInfo(map);
	for (typename ft::map<key1, ft::map<key2, value> >::iterator it = map.begin(); it != map.end(); it++) {
		std::cout << "Key = " << it->first << std::endl;
		for (typename ft::map<key2, value>::iterator inner = it->second.begin(); inner != it->second.end(); inner++) {
			std::cout << "Value->first = " << inner->first << "  |  Value->second = " << inner->second << std::endl;
		}
	}
}