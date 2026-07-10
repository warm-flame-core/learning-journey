#pragma once
#include <assert.h>

namespace xjw
{
	template<class T>
	struct list_Node
	{
		list_Node(const T date = T())
		{
			_date = date;
			_next = _prev = nullptr;
		}
		T _date;
		list_Node<T>* _next;
		list_Node<T>* _prev;
	};

	template<class T>
	struct list_iterator
	{
		typedef list_Node<T> Node;
		typedef list_iterator<T> Self;
		Node* _node;

		list_iterator(Node* node)
			:_node(node)
		{}

		T& operator*()
		{
			return _node->_date;
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self& operator--()
		{
			_node = _node->_next;
			return *this;
		}

		bool operator!=(const Self& s) const
		{
			return _node != s._node;
		}

		bool operator==(const Self& s) const
		{
			return _node == s._node;
		}
	};

	template<class T>
	class list
	{
	public:
		typedef list_Node<T> Node;
		typedef list_iterator<T> iterator;
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		void push_back(const T& x)
		{
			Node* ptail = _head->_prev;
			Node* newnode = new Node(x);
			newnode->_date = x;
			newnode->_next = _head;
			_head->_prev = newnode;
			ptail->_next = newnode;
			newnode->_prev = ptail;
			_size++;
		}

		size_t size() const
		{
			return _size;
		}

		bool empty()
		{
			return _size == 0;
		}

		iterator begin()
		{
			return _head->_next;
		}
		iterator end()
		{
			return _head;
		}
	private:
		Node* _head;
		size_t _size;
	};


	void my_list_test1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << ' ';
			++it;
		}
		cout << endl;
	}
}