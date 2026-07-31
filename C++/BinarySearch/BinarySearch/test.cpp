#include "BinarySearchTree.h"
int main()
{
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	key::BSTree<int> BST1;
	for (auto e : a)
	{
		BST1.Insert(e);
	}
	BST1.Inorder();
	int x;
	cin >> x;
	cout << BST1.Find(x) << endl;
	cout << BST1.Earse(x) << endl;
	BST1.Inorder();

	return 0;
}