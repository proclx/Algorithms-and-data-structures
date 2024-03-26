#pragma once
#include <iostream>
#include <iomanip>
#include <string>

const unsigned KEY_SETW = 5;
const unsigned VALUE_SETW = 20;

template<typename KeyType, typename ValueType>
class Table
{
private:
	KeyType tableKey;
	ValueType tableValue;
	Table<KeyType, ValueType>* left;
	Table<KeyType, ValueType>* right;
	bool isHead;
	bool isDeleted;
public:
	~Table()
	{
		if (this != nullptr)
		{
			std::cout << "DELETED:" << std::setw(KEY_SETW) << tableKey << std::setw(VALUE_SETW) << tableValue << std::endl;
		}
		if (left != nullptr)
		{
			delete left;
			left = nullptr;
		}
		if (right != nullptr)
		{
			delete right;
			right = nullptr;
		}
	}
	Table()
		: tableKey(KeyType()), tableValue(ValueType()), left(nullptr), right(nullptr), isHead(true), isDeleted(false)
	{
	}
	Table(KeyType key, ValueType val)
		: tableKey(key), tableValue(val), left(nullptr), right(nullptr), isHead(false), isDeleted(false)
	{
	}
	Table& Add(KeyType key, ValueType value)
	{
		if (isHead || isDeleted && (left == nullptr || left->tableKey < key) && ((right == nullptr || right->tableKey > key)))
		{
			tableKey = key;
			tableValue = value;
			isDeleted = false;
			isHead = false;
		}
		else if (key > tableKey)
		{
			if (right == nullptr)
			{
				right = new Table<KeyType, ValueType>(key, value);
			}
			else
			{
				right->Add(key, value);
			}
		}
		else if (key < tableKey)
		{
			if (left == nullptr)
			{
				left = new Table<KeyType, ValueType>(key, value);
			}
			else
			{
				left->Add(key, value);
			}
		}
		return *this;
	}
	void PrintTable() const
	{
		if (not isDeleted)
		{
			std::cout << std::setw(KEY_SETW) << tableKey << std::setw(VALUE_SETW) << tableValue << std::endl;
		}
		if (left != nullptr)
		{
			left->PrintTable();
		}
		if (right != nullptr)
		{
			right->PrintTable();
		}
	}
	void Remove(KeyType key)
	{
		if (this == nullptr)
		{
			throw(std::runtime_error("Table has no such value"));
		}
		else if (tableKey == key && !(isDeleted))
		{
			isDeleted = true;
		}
		else if (key > tableKey && right != nullptr)
		{
			right->Remove(key);
		}
		else if(key < tableKey && left != nullptr)
		{
			left->Remove(key);
		}
		else
		{
			throw(std::runtime_error("Table has no such value"));
		}
	}
	ValueType& operator[](KeyType key)
	{
		if (this == nullptr)
		{
			throw(std::runtime_error("Table has no such value"));
		}
		else if (tableKey == key && (!isDeleted))
		{
			return tableValue;
		}
		else if (key > tableKey)
		{
			return (*right)[key];
		}
		else if (key < tableKey)
		{
			return (*left)[key];
		}
	}
	bool Has(KeyType key)
	{
		if (this == nullptr)
		{
			return false;
		}
		else if (tableKey == key && (!isDeleted) && (!isHead))
		{
			return true;
		}
		else if (key > tableKey)
		{
			return right->Has(key);
		}
		else if (key < tableKey)
		{
			return left->Has(key);
		}
		else
		{
			return false;
		}
	}
};