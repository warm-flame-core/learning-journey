#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int BTDateType;
typedef struct BinaryTree
{
	BTDateType Date;
	struct BinaryTree* left;
	struct BinaryTree* right;
}BTNode;


//前序遍历
void PrevOrder(BTNode* root);

//中序遍历
void InOrder(BTNode* root);

//后序遍历
void PostOrder(BTNode* root);

//层序遍历
void LevelOnder(BTNode* root);

//二叉树节点个数
int BinaryTreeSize(BTNode* root);

//二叉树叶子的个数
int BinaryTreeLeafSize(BTNode* root);

//二叉树高度
int BinaryTreeHeight(BTNode* root);

//二叉树K层叶子的个数
int BinaryTreeLeafKSize(BTNode* root, int k);

//二叉树查找
BTNode* BinaryTreeFind(BTNode* root, int k);

//二叉树销毁
void BinaryTreeDestroy(BTNode* root);

//是否是完全二叉树
bool BinaryTreeComplete(BTNode* root);