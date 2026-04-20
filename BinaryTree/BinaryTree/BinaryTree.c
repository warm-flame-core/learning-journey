#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

typedef int BTDateType;
typedef struct BinaryTree
{
	BTDateType Date;
	struct BinaryTree* left;
	struct BinaryTree* right;
}BTNode;

BTNode* BuyNode(BTDateType x)
{
	BTNode* newnode = (BTNode*)malloc(sizeof(BTNode));
	if (newnode == NULL)
	{
		perror("malloc error");
		return;
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

//前序遍历
void PrevOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("N ");
		return;
	}
	
	printf("%d ", root->Date);
	PrevOrder(root->left);
	PrevOrder(root->right);
}

void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("N ");
		return;
	}

	InOrder(root->left);
	printf("%d ", root->Date);
	InOrder(root->right);
}

void PostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("N ");
		return;
	}

	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->Date);
}

//void LevelOnder(BTNode* root)
//{
//	if (root == NULL || root->left == NULL || root->right == NULL)
//	{
//		printf("N ");
//		return;
//	}
//	
//	printf("%d ", root->Date);
//	printf("%d ", root->left->Date);
//	printf("%d ", root->right->Date);
//	LevelOnder(root->left);
//	LevelOnder(root->right);
//}

//二叉树节点个数
//函数内置计数器在递归时重复初始化
//函数外部使用计数器需要重复初始化，非常麻烦
int BinaryTreeSize(BTNode* root)
{
	return root == NULL ? 0 : BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
}

//二叉树叶子的个数
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;
	return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
}
//二叉树的高度,效率有问题
//int count = 0;
//int BinaryTreeHeight(BTNode* root, int *pcount)
//{
//	(*pcount)++;
//	if (root == NULL)
//		return 0;
//	return BinaryTreeHeight(root->left, pcount) > BinaryTreeHeight(root->right, pcount) ? BinaryTreeHeight(root->left, pcount) + 1 : BinaryTreeHeight(root->right, pcount) + 1;
//}

//二叉树高度
int BinaryTreeHeight(BTNode* root)
{
	if (root == NULL)
		return 0;
	int leftheight = BinaryTreeHeight(root->left);
	int rightheight = BinaryTreeHeight(root->right);
	return leftheight > rightheight ? leftheight + 1 : rightheight + 1;
}


int BinaryTreeLeafKSize(BTNode* root, int k)
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BinaryTreeLeafKSize(root->left, k - 1) + BinaryTreeLeafKSize(root->right, k - 1);
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
	return 0;
}