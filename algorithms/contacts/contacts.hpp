#ifndef _CONTACTS_
#define _CONTACTS_

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class trie
{
	class node;
	typedef node* node_ptr;

	class node
	{
	public:
		friend class trie;

		node(char c):
			node(c, 0, nullptr) {}
		node(const std::string& s):
			node(s.begin(), s.end(), 0, nullptr) {}
		template<class InputIt>
		node(InputIt first, InputIt last):
			node(first, last, 0, nullptr) {}

		inline char key() const { return _key; }
		inline int depth() const { return _depth; }

		node_ptr create_child(char c)
		{
			auto found = child_exists(c);
			if(!(found.second))
			{
				node_ptr n = new node(c, _depth + 1, this);
				_children.push_back(n);
				return n;
			}

			return (found.first);
		}
		template<class InputIt>
		node_ptr create_child(InputIt first, InputIt last)
		{
			if(_children.size() > 0){
				auto t = child_exists(*first);
				if(t.second)
				{
					(t.first)->create_child(++first, last);
					return t.first;
			}}

			node_ptr n = new node(first, last, _depth + 1, this);
			_children.push_back(n);
			return n;
		}

		std::pair<node_ptr, bool> child_exists(char c)
		{
			auto f = std::find_if(_children.begin(), _children.end(), [&c](const auto& i)-> bool {
				return (c == i->_key);
			});
			return std::make_pair(*f, f == _children.end());
		}

	private:
		node(char c, int d, node_ptr p):
			_key(c), _depth(d), _parent(p) {}
		template<class InputIt>
		node(InputIt first, InputIt last, int d, node_ptr p):
			_key( (*first) ? (*first) : (throw std::invalid_argument("Iterator does not reference a valid character.") ) ), _depth(d), _parent(p)
		{
			if( (*(++first)) && (first <= last) )
			{
				node_ptr n = new node(first, last, _depth + 1, this);
				_children.push_back(n);
			}
		}

		const char _key;
		const int _depth;
		node_ptr _parent;

		std::vector<node_ptr> _children;
	};

public:
	trie();
	trie(const std::vector<std::string>& dict);
	template<class InputIt>
	trie(InputIt first, InputIt last);

	void add_word(const std::string& s);
	template<class InputIt>
	void add_word(InputIt first, InputIt last);

	~trie();

private:
	void delete_recursive(node_ptr root);

	int _keyword_count;


	node_ptr _root;
};

#endif