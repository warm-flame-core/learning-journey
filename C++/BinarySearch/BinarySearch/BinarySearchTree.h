#pragma once
#include <iostream>
#include <string>
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
		BSTree() = default;

		BSTree(const BSTree& BST)
		{
			_root = Copy(BST._root);
		}
		
		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}
		
		BSTree& operator=(BSTree tmp)
		{
			std::swap(_root, tmp._root);
			return *this;
		}

		
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
					else if (pcur->_right == nullptr)
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
						while (replace->_left)
						{
							replaceparent = replace;
							replace = replace->_left;
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
		Node* Copy(Node*& root)
		{
			if (root == nullptr)
				return nullptr;
			Node* newnode = new Node(root->_key);
			newnode->_left = Copy(root->_left);
			newnode->_right = Copy(root->_right);
			return newnode;
		}

		void Destroy(Node*& root)
		{
			if (root == nullptr) 
				return;
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
			root = nullptr;
		}

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

namespace key_value
{
	template<class K, class V>
	struct BinarySearchNodeTree
	{
		BinarySearchNodeTree(const K& key, const V& value)
			:_key(key)
			,_value(value)
			, _right(nullptr)
			, _left(nullptr)
		{}
		K _key;
		V _value;
		BinarySearchNodeTree<K, V>* _right;
		BinarySearchNodeTree<K, V>* _left;
	};


	template<class K, class V>
	class BSTree
	{
		using Node = BinarySearchNodeTree<K, V>;
	public:
		
		BSTree() = default;

		BSTree(const BSTree& BST)
		{
			_root = Copy(BST._root);
		}

		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}

		BSTree& operator=(BSTree tmp)
		{
			std::swap(_root, tmp._root);
			return *this;
		}

		bool Insert(const K& key, const V& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(key, value);
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
			pcur = new Node(key, value);
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
					else if (pcur->_right == nullptr)
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
						while (replace->_left)
						{
							replaceparent = replace;
							replace = replace->_left;
						}
						pcur->_key = replace->_key;
						pcur->_value = replace->_value;
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
		Node* Copy(Node*& root)
		{
			if (root == nullptr)
				return nullptr;
			Node* newnode = new Node(root->_key, root->_value);
			newnode->_left = Copy(root->_left);
			newnode->_right = Copy(root->_right);
			return newnode;
		}
		void Destroy(Node*& root)
		{
			if (root == nullptr) 
				return;
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
			root = nullptr;
		}
		void Inorder_Core(Node* root)
		{
			if (root == nullptr)
				return;
			Inorder_Core(root->_left);
			cout << root->_key << " : " << root->_value << ' ';
			Inorder_Core(root->_right);
		}
		Node* _root = nullptr;
	};

}