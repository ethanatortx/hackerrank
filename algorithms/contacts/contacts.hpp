#ifndef _CONTACTS_
#define _CONTACTS_

#include <cmath>
#include <iostream>

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <map>

class trie
{
	class node;
	typedef node* node_ptr;

	class node
	{
	public:
		friend class trie;

		node():
			node(0, 0, nullptr, 0) {}
		node(char c):
			node(c, 0, nullptr, 0) {}
		node(const std::string& s):
			node(s.begin(), s.end(), 0, nullptr, 0) {}
		template<class InputIt>
		node(InputIt first, InputIt last):
			node(first, last, 0, nullptr, (((first + 1) == last) ? (1) : (0)) ) {}

		inline char key() const { return _key; }
		inline int depth() const { return _depth; }
		node_ptr fail() 
		{
			return _fail;
		}

		node_ptr create_child(char c)
		{
			auto found = child_exists(c);
			if(!(found.second))
			{
				node_ptr n = new node(c, _depth + 1, this, 0);
				_children.push_back(n);
				return n;
			}

			return (found.first);
		}
		template<class InputIt>
		node_ptr create_child(InputIt first, InputIt last)
		{
			if(first != last && *first){
				if(_children.size() > 0){
					auto t = child_exists(*first);
					if(t.second)
					{
						(t.first)->create_child(++first, last);
						return t.first;
				}}

				node_ptr n = new node(first, last, _depth + 1, this, (((first + 1) == last) ? (1) : (0)));
				_children.push_back(n);
				return n;
			}
		}

		std::pair<node_ptr, bool> child_exists(char c)
		{
			auto f = std::find_if(_children.begin(), _children.end(), [&c](const auto& i)-> bool {
				return (c == i->_key);
			});
			return std::make_pair(*f, f != _children.end());
		}

	//private:
		node(char c, int d, node_ptr p, bool is):
			_key(c), _depth(d), _parent(p), _is_keyword(is), _fail(nullptr) {}
		template<class InputIt>
		node(InputIt first, InputIt last, int d, node_ptr p, bool is):
			_key( (*first) ? (*first) : (throw std::invalid_argument("Iterator does not reference a valid character." + std::to_string((char)(p->_key))) ) ), _depth(d), _parent(p), _is_keyword(is), _fail(nullptr)
		{
			if( (*(++first)) && (first <= last) )
			{
				node_ptr n = new node(first, last, _depth + 1, this, (((first + 1) == last) ? (1) : (0)) );
				_children.push_back(n);
			}
		}

		const bool _is_keyword;
		const char _key;
		const int _depth;
		
		node_ptr _parent;
		node_ptr _fail;
		std::vector<node_ptr> _children;
	};

public:
	//friend class node;

	trie():
		_root(new node()), _keyword_count(0), _longest(0) {}
	trie(const std::vector<std::string>& dict):
		trie(dict.begin(), dict.end()) {}

	template<class InputIt>
	trie(InputIt first, InputIt last):
		_root(new node()), _keyword_count(last - first), _longest(0)
	{
		while(first != last)
		{
			if(first->size() > _longest) _longest = first->size();
			_root->create_child(first->begin(), first->end());
			++first; 
		}
	}

	template<class InputIt>
	void add_word(InputIt first, InputIt last)
	{
		_root->create_child(first, last);
		if(last - first > _longest) _longest = last - first;
		++_keyword_count;
	}

	template<class InputIt>
	std::map<std::string, int> check(InputIt first, InputIt last)
	{

	}

	inline int keyword_count() const { return _keyword_count; }

	~trie() { delete_recursive(_root); }

//private:
	void calculate_fail()
	{
		for(auto i : _root->_children)
			i->_fail = _root;
		for(auto i : _root->_children)
			calculate_fail(i);
	}

	void calculate_fail(node_ptr root)
	{
		node_ptr current = root->_parent;

		while(current != nullptr)
		{
			current = current->_fail;
			auto check = current->child_exists(root->_key);
			if(check.second)
				root->_fail = check.first;
		}

		for(auto i : root->_children)
		{
			calculate_fail(i);
		}
	}

	void delete_recursive(node_ptr root)
	{
		for(const auto& i : root->_children)
			delete_recursive(i);
		delete root;
	}

	int _keyword_count;
	int _longest;
	node_ptr _root;
};

#endif