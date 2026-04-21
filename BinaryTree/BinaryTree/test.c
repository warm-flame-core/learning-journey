#define _CRT_SECURE_NO_WARNINGS 1
#include "BinaryTree.h"

BTNode* BuyNode(BTDateType x)
{
	BTNode* newnode = (BTNode*)malloc(sizeof(BTNode));
	if (newnode == NULL)
	{
		perror("malloc error");
		return NULL;
	}
	newnode->Date = x;
	newnode->right = newnode->left = NULL;
	return newnode;
}

BTNode* CreateBinaryTree()
{
	BTNode* node1 = BuyNode(1);
	BTNode* node2 = BuyNode(2);
	BTNode* node3 = BuyNode(3);
	BTNode* node4 = BuyNode(4);
	BTNode* node5 = BuyNode(5);
	BTNode* node6 = BuyNode(6);
	BTNode* node7 = BuyNode(7);

	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;
	node5->right = node7;
	return node1;
}


int main()
{
	BTNode* root = CreateBinaryTree();
	PrevOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	PostOrder(root);
	printf("\n");
	/*LevelOnder(root);
	printf("\n");*/
	printf("the BinaryTree size:%d\n", BinaryTreeSize(root));
	printf("the BinaryTree leaf size:%d\n", BinaryTreeLeafSize(root));
	/*BinaryTreeHeight(root, &count);
	printf("%d", count);*/
	printf("the BinaryTree height:%d\n", BinaryTreeHeight(root));
	printf("the BinarykTree size:%d\n", BinaryTreeLeafKSize(root, 4));
	BTNode* ret = BinaryTreeFind(root, 10);
	if (ret)
		printf("找到了\n");
	else
		printf("没找到\n");
	LevelOnder(root);
	printf("\n");
	return 0;
}