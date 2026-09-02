#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;

enum COLOUR
{
	RED,
	BLACK
};

template<class K, class V>
struct RBTreeNode
{
	pair<K, V> _kv;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	COLOUR _col;


	RBTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		,_col(RED)
	{}
};


template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}

		Node* parent = nullptr;
		Node* pcur = _root;
		while (pcur)
		{
			if (pcur->_kv.first < kv.first)
			{
				parent = pcur;
				pcur = pcur->_right;
			}
			else if (pcur->_kv.first > kv.first)
			{
				parent = pcur;
				pcur = pcur->_left;
			}
			else
			{
				return false;
			}
		}
		pcur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = pcur;
		}
		else
		{
			parent->_left = pcur;
		}
		pcur->_parent = parent;

		// 调整颜色
		// 用while需要持续网上调整颜色
		while(parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			// 大情况是按父亲在哪边分情况
			if (parent == grandfather->_left)
			{
				// 祖父左边是父亲，右边是叔叔
				//	g
				//f	  u
				Node* uncle = grandfather->_right;

				// 叔叔存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//继续向上处理
					pcur = grandfather;
					parent = pcur->_parent;
				}
				// 叔叔不存在或者叔叔存在且为黑
				// u不存在，则c⼀定是新增结点，u存在且为黑，则c⼀定不是新增，c之前是黑色的，是在c的⼦树中插入
				else
				{
					if (pcur == parent->_left)
					{
						// 孩子是父亲的左边，同一边用右单旋
						//		g
						//	f	  u
						//c
						RotateR(grandfather);
						grandfather->_col = RED;
						parent->_col = BLACK;
						
					}
					else
					{
						// 孩子是父亲的右边，不是纯粹的左边高
						//		g
						//	f	  u
						//    c
						RotateL(parent);
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}

			}
			else
			{
				// 祖父右边是父亲，左边是叔叔
				//	g
				//u	  f
				Node* uncle = grandfather->_left;
				// 叔叔存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//继续向上处理
					pcur = grandfather;
					parent = pcur->_parent;
				}
				// 叔叔不存在或者叔叔存在且为黑
				// u不存在，则c⼀定是新增结点，u存在且为黑，则c⼀定不是新增，c之前是黑色的，是在c的⼦树中插入
				else
				{
					if (pcur == parent->_left)
					{
						// 孩子是父亲的右边，同一边用左单旋
						//		g
						//	u	  f
						//         c
						RotateL(grandfather);
						grandfather->_col = RED;
						parent->_col = BLACK;

					}
					else
					{
						// 孩子是父亲的右边，不是纯粹的左边高
						//		g
						//	u		f
						//		  c
						RotateR(parent);
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}


		// 每次保证根节点是黑色的
		_root->_col = BLACK;

		return true;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;


		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* pparent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;
		if (pparent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (pparent->_right == parent)
			{
				pparent->_right = subL;
			}
			else
			{
				pparent->_left = subL;
			}
			subL->_parent = pparent;
		}
	}

	void RotateL(Node* parent)
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



	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	int Height()
	{
		return _Height(_root);
	}

	int Size()
	{
		return _Size(_root);
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return nullptr;
	}

	bool IsBalance()
	{
		if (_root == nullptr)
			return true;

		if (_root->_col == RED)
			return false;

		// 参考值
		int refNum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				++refNum;
			}
			cur = cur->_left;
		}

		return Check(_root, 0, refNum);
	}

private:

	bool Check(Node* root, int blackNum, const int refNum)
	{
		if (root == nullptr)
		{
			// 前序遍历走到空时，意味着一条路径走完了
			//cout << blackNum << endl;
			if (refNum != blackNum)
			{
				return;
			}
			return true;
		}

		// 检查孩子不太方便，因为孩子有两个，且不一定存在，反过来检查父亲就方便多了
		if (root->_col == RED && root->_parent->_col == RED)
		{
			return;
		}

		if (root->_col == BLACK)
		{
			blackNum++;
		}

		return Check(root->_left, blackNum, refNum)
			&& Check(root->_right, blackNum, refNum);
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}

	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	int _Size(Node* root)
	{
		if (root == nullptr)
			return 0;

		return _Size(root->_left) + _Size(root->_right) + 1;
	}

private:
	Node* _root = nullptr;
};