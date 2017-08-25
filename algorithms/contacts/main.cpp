#include "contacts.hpp"

#include <functional>

int main()
{
	std::vector<std::string> svec = {
		"oran", "orang", "ort", "odo", "opt", "or"
	};
	auto t = trie(svec);

	
	return 0;
}