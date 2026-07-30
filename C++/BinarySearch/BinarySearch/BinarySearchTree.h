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