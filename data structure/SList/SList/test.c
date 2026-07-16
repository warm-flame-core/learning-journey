#include "List.h"
void test01()
{
	LTNode* plist = LTInit();
	LTPushBack(plist, 1);
	LTPushBack(plist, 2);
	LTPushBack(plist, 3);
	LTPrint(plist);
	/*LTPushFront(plist, 5);
	LTPrint(plist);
	LTPopBack(plist);
	LTPrint(plist);
	LTPopFront(plist);
	LTPrint(plist);*/
	LTNode* find = LTFind(plist, 3);
	/*LTInsert(find, 5);
	LTPrint(plist);*/
	LTErase(find);
	LTPrint(plist);
}

int main()
{
	test01();
	return 0;
}