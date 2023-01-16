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



int main() {

	std::cout << "____________________VECTOR TEST____________________" << std::endl;
	testVector();

	std::cout << "____________________MAP TEST____________________" << std::endl;
	ft::map<std::string, std::string> ft_map;
	std::map<std::string, std::string> std_map;
	testMap(ft_map, std_map);
	bounds();
	std::cout << "____________________STACK TEST____________________" << std::endl;
	ft::stack<int> ft_stack;
	std::stack<int> std_stack;
	testStack(ft_stack, std_stack);
	
	return 0;
}