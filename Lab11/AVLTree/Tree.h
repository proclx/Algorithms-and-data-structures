#pragma once
#include <functional>

template<typename T>
struct TreeNode
{
public:
	T value;
	TreeNode<T>* left;
	TreeNode<T>* right;
	int balance;

	TreeNode(const T& val)
		: value(val), left(nullptr), right(nullptr), balance(0)
	{
	}
};

template<typename T>
int Height(TreeNode<T>* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	else
	{
		int hLeft = Height(root->left);
		int hRight = Height(root->right);
		if (hLeft > hRight)
		{
			return hLeft + 1;
		}
		else
		{
			return hRight + 1;
		}
	}
}

template<typename T>
void SetBalance(TreeNode<T>* root)
{
	if (root != nullptr)
	{
		root->balance = Height(root->right) - Height(root->left);
	}
}

template<typename T>
void TurnRight(TreeNode<T>*& root)
{
	TreeNode<T>* leftSubtree;
	TreeNode<T>* leftSubtreeRightSubtree;
	leftSubtree = root->left;
	leftSubtreeRightSubtree = root->left->right;

	leftSubtree->right = root;
	root->left = leftSubtreeRightSubtree;
	root = leftSubtree;
	SetBalance(root->right);
	SetBalance(root);
}

template<typename T>
void TurnLeft(TreeNode<T>*& root)
{
	TreeNode<T>* rightSubtree;
	TreeNode<T>* rightSubtreeLeftSubtree;
	rightSubtree = root->right;
	rightSubtreeLeftSubtree = root->right->left;

	rightSubtree->left = root;
	root->right = rightSubtreeLeftSubtree;
	root = rightSubtree;
	SetBalance(root->left);
	SetBalance(root);
}

template<typename T, class Comparator = std::less<T>>
void _Insert(TreeNode<T>*& tree, const T& val, Comparator comparator = Comparator())
{
	if (tree == nullptr)
	{
		tree = new TreeNode<T>(val);
	}
	else
	{
		// val < tree->value
		if (comparator(val, tree->value))
		{
			_Insert(tree->left, val, comparator);
			if (Height(tree->left) - Height(tree->right) > 1)
			{
				if (Height(tree->left->left) - Height(tree->left->right) > 1)
				{
					TurnLeft(tree->left);
				}
				TurnRight(tree);
			}
		}
		else
		{
			_Insert(tree->right, val, comparator);
			if (Height(tree->right) - Height(tree->left) > 1)
			{
				if (Height(tree->right->right) - Height(tree->right->left) > 1)
				{
					TurnRight(tree->right);
				}
				TurnLeft(tree);
			}
		}
		SetBalance(tree);
	}
}

template<typename T, class Comparator = std::less<T>>
TreeNode<T>* _Delete(TreeNode<T>* tree, const T& val, Comparator comparator = Comparator())
{
	if (tree == nullptr)
	{
		return tree;
	}
	if (comparator(val, tree->value))
	{
		tree->left = _Delete(tree->left, val, comparator);
	}
	else if (comparator(tree->value, val))
	{
		tree->right = _Delete(tree->right, val, comparator);
	}
	else
	{
		if (tree->left == nullptr || tree->right == nullptr)
		{
			TreeNode<T>* temp = tree->left ? tree->left : tree->right;
			if (temp == nullptr)
			{
				temp = tree;
				tree = nullptr;
			}
			else
			{
				*tree = *temp;
				delete temp;
			}
		}
		else
		{
			TreeNode<T>* temp = tree->right;
			while (temp->left != nullptr)
			{
				temp = temp->left;
			}
			tree->value = temp->value;
			tree->right = _Delete(tree->right, temp->value, comparator);
		}
	}
	if (tree == nullptr)
	{
		return tree;
	}
	SetBalance(tree);
	if (tree->balance > 1)
	{
		if (Height(tree->right->right) - Height(tree->right->left) < 0)
		{
			TurnRight(tree->right);
		}
		TurnLeft(tree);
	}
	else if (tree->balance < -1)
	{
		if (Height(tree->left->left) - Height(tree->left->right) > 0)
		{
			TurnRight(tree->left);
		}
		TurnRight(tree);
	}
	return tree;
}



template<typename T>
void PrintTree(TreeNode<T>* node, std::ostream& os = std::cout, int indent = 0)
{
	if (node == nullptr)
	{
		return;
	}
	PrintTree(node->right, os, indent + 1);
	for (int i = 0; i < indent; ++i)
	{
		os << '\t';
	}
	os << node->value << '\n';
	PrintTree(node->left, os, indent + 1);
}

template<typename T, class Comparator = std::less<T>>
bool _Has(TreeNode<T>* node, const T& val, Comparator comparator = Comparator())
{
	if (node == nullptr)
	{
		return false;
	}
	else if (node->value == val)
	{
		return true;
	}
	else
	{
		if (comparator(node->value, val))
		{
			return _Has(node->left, val, comparator);
		}
		else
		{
			return _Has(node->left, val, comparator);
		}
	}
}

template<typename T, class Comparator = std::less<T>>
class AVLTree
{
public:
	typedef TreeNode<T>* Tree;
private:
	Tree tree;
public:
	AVLTree()
		: tree(nullptr)
	{
	}
	AVLTree(const T& val)
		: tree(new TreeNode<T>(val))
	{
	}
	void Print(std::ostream& os = std::cout)
	{
		PrintTree(tree);
	}
	AVLTree& Insert(const T& val)
	{
		if (tree == nullptr)
		{
			tree = new TreeNode<T>(val);
		}
		else
		{
			_Insert(tree, val, Comparator());
		}
		return *this;
	}
	const Tree Data() const
	{
		return tree;
	}
	AVLTree& Remove(const T& val)
	{
		_Delete(tree, val, Comparator());
		return *this;
	}
	bool Has(const T& val) const
	{
		return _Has(tree, val, Comparator());
	}
};