#pragma once
#include <iostream>
using namespace std;
enum Colour
{
	RED,
	BLACK
};

template<class T>
struct RBTreeNode
{
	// 这里更新控制平衡也要加入parent指针
	T _data;
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Colour _col;

	RBTreeNode(const T& data)
		:_data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};

template<class T,class Ref,class Ptr>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, Ref, Ptr> Self;


	Node* _node;
	// 增加一个_root。前置减的时候不会空指针解引用
	Node* _root;

	RBTreeIterator(Node* node,Node* root)
		:_node(node)
		,_root(root)
	{}

	Self& operator++()
	{
		// 如果所在节点右边不为空，下一次要访问的节点就是右子树的最左节点
		if (_node->_right)
		{
			Node* min = _node->_right;
			while (min->_left)
			{
				min = min->_left;
			}
			_node = min;
		}
		// 如果所在节点右边为空，说明所在节点所属的子树已经访问完了
		// 1.如果所在节点是其父亲的左，说明下一个节点就是父节点
		// 2.如果所在节点是其父亲的右，说明父节点也访问完了需要继续往上
		// 3.知道节点是祖先的左，则下一个就要访问那个祖先
		else
		{
			Node* pcur = _node;
			Node* parent = _node->_parent;
			// 如果父亲为空，说明父亲已经到了最右边的节点的下一个
			// 用父亲不能为空保证迭代器区间的右边可以是空指针
			// 即End
			while (parent && pcur == parent->_right)
			{
				pcur = parent;
				parent = pcur->_parent;
			}
			_node = parent;
		}

		return *this;
	}


	Self& operator--()
	{
		// 如果是从End开始减，空指针减不了
		// 可以迭代器新增一个成员_root，
		// 外面传递参数的时候明确根节点，
		// 从end减下一个节点就是树的最有节点
		if (_node == nullptr)
		// 走到这里说明次数是end，下一个是树的最右节点
		{
			Node* Mostright = _root;
			while (Mostright && Mostright->_right)
			{
				Mostright = Mostright->_right;
			}
			_node = Mostright;
		}
		// 如果所在节点左边不为空，下一次要访问的节点就是左子树的最右节点
		else if (_node->_left)
		{
			Node* rightMost = _node->_left;
			while (rightMost->_right)
			{
				rightMost = rightMost->_right;
			}
			_node = rightMost;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &(_node->_data);
	}

	bool operator!=(const Self& Iterator)
	{
		return _node != Iterator._node;
	}

	bool operator==(const Self& Iterator)
	{
		return _node == Iterator._node;
	}
};


// 封装的时候不知道红黑树是K的还是kv的，所以需要仿函数控制比较逻辑
// 对于map，比较的时候需要pair的first
// 对于set，比较需要K
template<class K, class T,class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef RBTreeIterator<T, T&, T*> Iterator;
	typedef RBTreeIterator<T, const T&, const T*> Const_Iterator;

	Iterator Begin()
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return Iterator(cur,_root);
	}

	Iterator End()
	{
		return Iterator(nullptr,_root);
	}


	Const_Iterator Begin() const
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return Const_Iterator(cur, _root);
	}

	Const_Iterator End() const
	{
		return Const_Iterator(nullptr, _root);
	}

	// stl库里面插入的返回值是
	//bool Insert(const T& data)
	pair<Iterator,bool> Insert(const T& data)
	{
		// 仿函数可以认为是类型，需要先创建对象才能使用
		KeyOfT kot;
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;

			// 单参数可以走隐式类型，C++1之后可以多参数隐式类型转换
			//return pair<Iterator, bool>(Iterator(_root, _root), true);
			return { Iterator(_root, _root), true };
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(cur->_data) > kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				/*return false;*/
				return { Iterator(cur, _root), false };
			}
		}

		cur = new Node(data);

		// 如果要支持返回pair类型，就不能是cur
		// 因为这样cur到后面因为旋转可能会动，所以要记录一下
		Node* newnode = cur;


		cur->_col = RED;
		if (kot(parent->_data) < kot(data))
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		// 链接父亲
		cur->_parent = parent;

		// 父亲是红色，出现连续的红色节点，需要处理
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				//   g
				// p   u
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					// 变色
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						//     g
						//   p    u
						// c
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//      g
						//   p    u
						//     c
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					break;
				}
			}
			else
			{
				//   g
				// u   p
				Node* uncle = grandfather->_left;
				// 叔叔存在且为红，-》变色即可
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 叔叔不存在，或者存在且为黑
				{
					// 情况二：叔叔不存在或者存在且为黑
					// 旋转+变色
					//   g
					// u   p
					//       c
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					break;
				}
			}
		}

		_root->_col = BLACK;

		return { Iterator(newnode, _root), true };
	}

	void RotateR(Node * parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* pParent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (pParent->_left == parent)
			{
				pParent->_left = subL;
			}
			else
			{
				pParent->_right = subL;
			}

			subL->_parent = pParent;
		}
	}

	void RotateL(Node * parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* parentParent = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;
		if (parentParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
			subR->_parent = parentParent;
		}
	}

	Node* Find(const K& key)
	{
		KeyOfT kot;
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < key)
				cur = cur->_right;
			else if (kot(cur->_data) > key)
				cur = cur->_left;
			else
				return cur;
		}
		return nullptr;
	}

private:
	Node* _root = nullptr;
};
