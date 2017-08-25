#include "contacts.hpp"

/*void print(trie::node* n, std::vector<std::vector<char> >& v, int x, int y)
{
	v[y][x] = n->_key;
	for(auto i : n->_children)
	{
		print(i, v, x++, y + 1);
	}
}
*/
int main()
{
	std::vector<std::string> svec = {
		"jeremy", "jesus", "jean", "jealon"
	};

	auto t = trie(svec);
/*	
	std::vector<std::vector<char> > v(t._longest + 1, std::vector<char>(t._keyword_count));
	print(t._root, v, 0, 0);

	int count = 0;
	for(const auto& i : v){
		std::cout << ++count << ": ";
		for(const auto& o : i)
			std::cout << o << ' ';
		std::cout << '\n';
	}*/

	return 0;
}