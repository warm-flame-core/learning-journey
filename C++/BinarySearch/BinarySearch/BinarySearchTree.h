#pragma once
#include <iostream>
using namespace std;
namespace key
{
	template<class K>
	struct BinarySearchNodeTree
	{
		BinarySearchNodeTree(const K& key)
			:_key(key)
			, _right(nullptr)
			, _left(nullptr)
		{}
		K _key;
		BinarySearchNodeTree<K>* _right;
		BinarySearchNodeTree<K>* _left;
	};


	template<class K>
	class BSTree
	{
		using Node = BinarySearchNodeTree<K>;
	public:
		bool Insert(const K& key)
		{
			if (_root == nullptr)
			{
				_root = new Node(key);
				return true;
			}
			Node* parent = nullptr;
			Node* pcur = _root;
			while (pcur)
			{
				parent = pcur;
				if (pcur->_key > key)
				{
					pcur = pcur->_left;
				}
				else if (pcur->_key < key)
				{
					pcur = pcur->_right;
				}
				else
				{
					return false;
				}
			}
			pcur = new Node(key);
			if (parent->_key < key)
				parent->_right = pcur;
			else
				parent->_left = pcur;
			return true;
		}
		bool Find(const K& key)
		{
			Node* pcur = _root;
			while (pcur)
			{
				if (pcur->_key > key)
				{
					pcur = pcur->_left;
				}
				else if (pcur->_key < key)
				{
					pcur = pcur->_right;
				}
				else
				{
					return true;
				}
			}
			return false;
		}

		bool Earse(const K& key)
		{
			Node* pcur = _root;
			Node* parent = nullptr;
			while (pcur)
			{
				if (pcur->_key > key)
				{
					parent = pcur;
					pcur = pcur->_left;
				}
				else if (pcur->_key < key)
				{
					parent = pcur;
					pcur = pcur->_right;
				}
				// 找到了要删除的节点
				else
				{
					// 左边孩子为空
					if (pcur->_left == nullptr)
					{
						// 1.pcur是根节点
						if (pcur == _root)
						{
							_root = pcur->_right;
							delete pcur;
						}
						// 2.pcur不是根节点
						else
						{
							// 如果pcur是父亲的右节点，那么将pcur的孩子接在父亲的右节点
							if (parent->_right == pcur)
							{
								parent->_right = pcur->_right;
								delete pcur;
							}
							else
							{
								parent->_left = pcur->_right;
								delete pcur;
							}
						}
					}
					// 右边孩子为空
					else if (pcur->_left == nullptr)
					{
						// 1.pcur是根节点
						if (pcur == _root)
						{
							_root = pcur->_left;
							delete pcur;
						}
						// 2.pcur不是根节点
						else
						{
							// 如果pcur是父亲的右节点，那么将pcur的孩子接在父亲的右节点
							if (parent->_right == pcur)
							{
								parent->_right = pcur->_left;
								delete pcur;
							}
							else
							{
								parent->_left = pcur->_left;
								delete pcur;
							}
						}
					}
					// 左右孩子都不为空，从pcur右边找比pcur大的最小节点交换
					else
					{
						Node* replaceparent = pcur;
						Node* replace = pcur->_right;
						while (pcur->_left)
						{
							replaceparent = pcur;
							pcur = pcur->_left;
						}
						pcur->_key = replace->_key;
						// replace是在左孩子为空时找到，所以时左孩子为空的情况
						if (replaceparent->_right == replace)
						{
							replaceparent->_right = replace->_right;
							delete replace;
						}
						else
						{
							replaceparent->_left = replace->_right;
							delete replace;
						}
					}
					return true;
				}
			}
			return false;
		}

		// 共有函数类外面调用无法用类里面的隐私参数，套一层
		void Inorder()
		{
			Inorder_Core(_root);
		}
	private:
		void Inorder_Core(Node* root)
		{
			if (root == nullptr)
				return;
			Inorder_Core(root->_left);
			cout << root->_key << " ";
			Inorder_Core(root->_right);
		}
		Node* _root = nullptr;
	};

}