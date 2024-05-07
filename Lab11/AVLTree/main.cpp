#include <iostream>
#include "Tree.h"

int main()
{
	AVLTree<int> AVL{ 5 };
	AVL.Insert(4);
	AVL.Insert(7);
	AVL.Insert(6);
	AVL.Insert(8);
	AVL.Insert(9);
	AVL.Insert(3);
	AVL.Insert(2);

	std::cout << std::boolalpha << AVL.Has(3) << ' ' << AVL.Has(10) << std::endl;

	PrintTree(AVL.Data());
	return 0;
}