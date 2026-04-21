#define _CRT_SECURE_NO_WARNINGS 1
#include "BinaryTree.h"
#include "Queue.h"

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

void LevelOnder(BTNode* root)
{
	if (root == NULL)
		return;
	Queue q;
	QueueInit(&q);
	QueuePush(&q, root);
	while (!QueneEmpty(&q))
	{
		BTNode* node = QueueFront(&q);
		QueuePop(&q);
		printf("%d ", node->Date);
		if(node->left)
			QueuePush(&q, node->left);

		if (node->right)
			QueuePush(&q, node->right);
	}
	QueueDestroy(&q);
}

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

//二叉树K层叶子的个数
int BinaryTreeLeafKSize(BTNode* root, int k)
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BinaryTreeLeafKSize(root->left, k - 1) + BinaryTreeLeafKSize(root->right, k - 1);
}

//二叉树查找
BTNode* BinaryTreeFind(BTNode* root, int k)
{
	if (root == NULL)
		return NULL;
	if (root->Date == k)
		return root;
	BTNode* ret = BinaryTreeFind(root->left, k);
	if (ret)
		return ret;
	return BinaryTreeFind(root->right, k);
}

void BinaryTreeDestroy(BTNode* root)
{
	if (root == NULL)
		return;
	BinaryTreeDestroy(root->left);
	BinaryTreeDestroy(root->right);
	free(root);
}


//是否是完全二叉树
bool BinaryTreeComplete(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	QueuePush(&q, root);
	while (!QueneEmpty(&q))
	{
		BTNode* node = QueueFront(&q);
		QueuePop(&q);
		if (node == NULL)
			break;
		QueuePush(&q, node->left);
		QueuePush(&q, node->right);
	}
	while (!QueneEmpty(&q))
	{
		BTNode* node = QueueFront(&q);
		QueuePop(&q);
		if (node != NULL)
		{
			QueueDestroy(&q);
			return false;
		}
	}
	QueueDestroy(&q);
	return true;
}