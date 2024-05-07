#include "pch.h"
#include "CppUnitTest.h"
#include "../AVLTree/Tree.h"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		/*
		
				1
			   / \
			  2   3
			 / \   \
			4   5   6
		   /
		  7

		*/
		TEST_METHOD(CalcHeight_) 
		{
			TreeNode<int> tree(1);
			tree.left = new TreeNode<int>(2);
			tree.left->left = new TreeNode<int>(4);
			tree.left->right = new TreeNode<int>(5);
			tree.left->left->left = new TreeNode<int>(7);
			tree.right = new TreeNode<int>(3);
			tree.right->right = new TreeNode<int>(6);
			Assert::AreEqual(Height(&tree), 4);
		}
		/*
		
				5
			   / \
			  4   7
			     / \
				6   8

		*/
		TEST_METHOD(Insert_)
		{
			AVLTree<int> tree(5);
			tree.Insert(4);
			tree.Insert(7);
			tree.Insert(6);
			tree.Insert(8);
			Assert::AreEqual(tree.Data()->value, 5);
			Assert::AreEqual(tree.Data()->left->value, 4);
			Assert::AreEqual(tree.Data()->right->value, 7);
			Assert::AreEqual(tree.Data()->right->left->value, 6);
			Assert::AreEqual(tree.Data()->right->right->value, 8);
		}
		TEST_METHOD(LeftRotation_)
		{
			AVLTree<int> tree(5);
			tree.Insert(4);
			tree.Insert(7);
			tree.Insert(6);
			tree.Insert(8);
			tree.Insert(9);
			Assert::AreEqual(tree.Data()->value, 7);
			Assert::AreEqual(tree.Data()->left->value, 5);
			Assert::AreEqual(tree.Data()->left->left->value, 4);
			Assert::AreEqual(tree.Data()->left->right->value, 6);
			Assert::AreEqual(tree.Data()->right->value, 8);
			Assert::AreEqual(tree.Data()->right->right->value, 9);
		}
		TEST_METHOD(RightRotation_)
		{
			AVLTree<int> tree(5);
			tree.Insert(4);
			tree.Insert(7);
			tree.Insert(6);
			tree.Insert(8);
			tree.Insert(9);
			tree.Insert(3);
			tree.Insert(2);
			Assert::AreEqual(tree.Data()->value, 7);
			Assert::AreEqual(tree.Data()->left->value, 5);
			Assert::AreEqual(tree.Data()->left->left->value, 3);
			Assert::AreEqual(tree.Data()->left->left->left->value, 2);
			Assert::AreEqual(tree.Data()->left->left->right->value, 4);
			Assert::AreEqual(tree.Data()->left->right->value, 6);
			Assert::AreEqual(tree.Data()->right->value, 8);
			Assert::AreEqual(tree.Data()->right->right->value, 9);
		}
	};
}
