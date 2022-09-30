#include <iostream>
#include <functional> // std::less
#include <map>

int main()
{
	bool k = std::less<int>()(11, 11);
	std::cout << k << std::endl;

	std::pair<std::pair<int, float>, float> t;
	t.first.first = 1;
	t.first.second = 1.1;
	t.second = 2.2;
	std::cout << t.first.first << std::endl;

	std::map<std::pair<std::pair<int, float>, int >, float > mymap;
	// mymap.insert()
	// mymap.key_comp()
}
