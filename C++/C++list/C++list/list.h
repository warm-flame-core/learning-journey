#pragma once
#include <assert.h>

namespace xjw
{
	// 定义每个节点
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


	// const iterator，const在*左边，表示指针不能更改
	// const_iterator，迭代器只读，不能修改所指向的东西

	// 两种迭代器十分相似，扩展模板参数，将两种迭代器合成一种，让编译器去推导
	template<class T, class Ref, class Ptr>
	struct list_iterator
	{
		typedef list_Node<T> Node;
		typedef list_iterator<T, Ref, Ptr> Self;
		Node* _node;


		// 写一个模板函数用普通迭代器构造const迭代器，权限缩小更符合逻辑
		// 这个函数效果等同拷贝构造函数，如果需要完善还需要显式的拷贝构造函数
		template<class Ref2, class Ptr2>
		list_iterator(const list_iterator<T, Ref2, Ptr2> lt)
			:_node(lt._node)
		{}

		list_iterator(Node* node)
			:_node(node)
		{}

		Ref operator*()
		{
			return _node->_date;
		}

		Ptr operator->()
		{
			return &(_node->_date);
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		// 后置运算符需要返回函数内部的值，不能加引用
		Self operator++(int)
		{
			Self tmp = *this;
			_node = _node->_next;
			return tmp;
		}
		Self operator--(int)
		{
			Self tmp = *this;
			_node = _node->_prev;
			return tmp;
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


	//两者可以合并，全部让编译器自己推理
	/*template<class T>
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

		T* operator->()
		{
			return &(_node->_date);
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self& operator--()
		{
			_node = _node->_prev;
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
	struct list_const_iterator
	{
		typedef list_Node<T> Node;
		typedef list_const_iterator<T> Self;
		const Node* _node;

		list_const_iterator(const Node* node)
			:_node(node)
		{}

		const T& operator*()
		{
			return _node->_date;
		}

		const T* operator->()
		{
			return &(_node->_date);
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self& operator--()
		{
			_node = _node->_prev;
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
	};*/

	template<class T>
	class list
	{
	public:
		typedef list_Node<T> Node;
		//typedef list_iterator<T> iterator;
		//typedef list_const_iterator<T> const_iterator;
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;
		list()
		{
			empty_init();
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		list(const list<T>& lt)
		{
			empty_init();
			for (auto e : lt)
			{
				push_back(e);
			}
		}

		// 现代写法，不引用是拷贝的临时变量交换后直接销毁
		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}
		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		// 写一个连哨兵位都没有的链表的初始化，方便复用
		void empty_init()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		void clear()
		{
			auto it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		void push_back(const T& x)
		{
			/*Node* ptail = _head->_prev;
			Node* newnode = new Node(x);
			newnode->_next = _head;
			_head->_prev = newnode;
			ptail->_next = newnode;
			newnode->_prev = ptail;
			_size++;*/
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		//添加后返回新的节点的迭代器
		iterator insert(iterator pos, const T& x)
		{
			Node* pcur = pos._node;
			Node* prev = pcur->_prev;
			Node* newnode = new Node(x);
			newnode->_next = pcur;
			newnode->_prev = prev;
			pcur->_prev = newnode;
			prev->_next = newnode;
			++_size;
			return newnode;
		}

		//返回被删除的下一个的迭代器
		iterator erase(iterator pos)
		{
			assert(pos != end());
			// prev pos._node pcur
			Node* pcur = pos._node->_next;
			Node* prev = pos._node->_prev;
			pcur->_prev = prev;
			prev->_next = pcur;
			delete pos._node;
			--_size;
			return pcur;
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

		// const修饰的必须返回const迭代器
		const_iterator begin() const
		{
			return _head->_next;
		}
		const_iterator end() const
		{
			return _head;
		}
	private:
		Node* _head;
		size_t _size;
	};

	template<class Container>
	void container_print(const Container& v)
	{
		for (auto e : v)
		{
			cout << e << ' ';
		}
		cout << endl;
	}



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
		it = lt.begin();
		lt.insert(it, 100);
		it = lt.begin();

		while (it != lt.end())
		{
			cout << *it << ' ';
			++it;
		}
		it = lt.begin();
		lt.erase(it);
		it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << ' ';
			++it;
		}
	}

	void my_list_test2()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		list<int>::iterator it = lt.begin();
		lt.erase(it);
		it = lt.begin();
		container_print(lt);
		it = ++lt.begin();
		lt.insert(it, 100);
	}
}