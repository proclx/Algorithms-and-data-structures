#pragma once
#include <stdexcept>
#include <iostream>

template<typename T>
class SparseMatrix
{
private:
	typedef T TypeValue;
	struct Node
	{
	public:
		int row;
		int column;
		TypeValue value;
		Node* right;
		Node* down;
		Node(TypeValue val = TypeValue())
			: row(-1), column(-1), value(val), right(this), down(this)
		{
		}
	};
	unsigned rowN;
	unsigned columnN;
	Node* rows;
	Node* columns;

	bool Check(Node* row, Node* column)
	{
		bool result = false;
		//std::cout << row->right << '\n' << column->down << '\n' << std::boolalpha << (row->right == column->down) << '\n';
		if (row->right == column->down)
		{
			result = true;
		}
		return result;
	}
public:
	SparseMatrix(unsigned rows, unsigned columns)
		: rowN(rows), columnN(columns), rows(new Node[rows]), columns(new Node[columns])
	{
	}
	~SparseMatrix()
	{
		for (unsigned i = 0; i < rowN; ++i)
		{
			Node* curr = rows[i].right;
			while (curr != &rows[i])
			{
				Node* toDelete = curr;
				curr = curr->right;
				delete toDelete;
			}
		}
		delete[] rows;
		delete[] columns;
	}
	Node* GetPrevByRow(unsigned i, unsigned j) const
	{
		Node* curr = &rows[i];
		while (curr->right->column != -1 && curr->right->column < j)
		{
			curr = curr->right;
		}
		return curr;
	}
	Node* GetPrevByCol(unsigned j, unsigned i) const
	{
		Node* curr = &columns[j];
		while (curr->down->row != -1 && curr->down->row < i)
		{
			curr = curr->down;
		}
		return curr;
	}
	void Add(unsigned i, unsigned j, const TypeValue& value)
	{
		Node* prevRow = GetPrevByRow(i, j);
		Node* prevCol = GetPrevByCol(j, i);

		if (prevRow->right->row == i && prevCol->down->column == j)
		{
			throw(std::runtime_error("void Add::Already has value"));
		}
		else
		{
			Node* item = new Node(value);
			item->row = i;
			item->column = j;

			item->right = prevRow->right;
			prevRow->right = item;

			item->down = prevCol->down;
			prevCol->down = item;

			if (!Check(prevRow, prevCol))
			{
				throw(std::runtime_error("void Add::runtime_error"));
			}
		}
	}

	TypeValue& Get(unsigned i, unsigned j) 
	{
		Node* prevRow = GetPrevByRow(i, j);
		Node* prevCol = GetPrevByCol(j, i);
		if (!Check(prevRow, prevCol))
		{
			throw(std::runtime_error("TypeValue& Get Add::runtime_error"));
		}
		else
		{
			return prevRow->right->value;
		}
	}

	bool Has(unsigned i, unsigned j)
	{
		Node* prevRow = GetPrevByRow(i, j);
		Node* prevCol = GetPrevByCol(j, i);
		if(Check(prevRow, prevCol))
		{
			return true;
		}
	}

	void Remove(unsigned i, unsigned j)
	{
		Node* prevRow = GetPrevByRow(i, j);
		Node* prevCol = GetPrevByCol(j, i);

		if (Check(prevRow, prevCol))
		{
			Node* toDelete = prevRow->right;
			prevRow->right = prevRow->right->right;
			prevCol->down = prevCol->down->down;
			delete toDelete;
		}
		else
		{
			throw(std::runtime_error("void Remove::has no such value"));
		}
	}

	void Print(std::ostream& os = std::cout)
	{
		for (unsigned i = 0; i < rowN; ++i)
		{
			for (unsigned j = 0; j < columnN; ++j)
			{
				if (this->Has(i, j))
				{
					os << this->Get(i, j);
				}
				else
				{
					os << '0';
				}
				os << ' ';
			}
			os << '\n';
		}
	}
};