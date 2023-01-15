#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "includes/vector.hpp"
#include "includes/map.hpp"

int		main(void)
{
	std::map<int, std::string> mp;

	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	std::map<int, std::string>::const_iterator it = mp.begin();
	std::map<int, std::string>::const_iterator it2 = mp.end();
	for (; it != it2; ++it){
		std::cout << it->first << "   " << it->second << std::endl;
	}
	return (0);
}