#pragma once
#include <iostream>
#include <string>

const unsigned SET_W_PROPERTIES_FOR_KEY = 5;
const unsigned SET_W_PROPERTIES_FOR_INT_VALUE = 5;
const unsigned SET_W_PROPERTIES_FOR_STRING_VALUE = 25;

struct TableValue
{
public:
	int intValue;
	std::string stringValue;
	TableValue();
	TableValue(int value, const std::string& sValue);
	TableValue* Copy() const;
};

struct TableKey
{
public:
	int key;
	TableValue* value;
	bool IsEmpty() const;
	int GetKey() const;
	void Print(std::ostream& os = std::cout) const;
	TableKey();
	~TableKey();
};

class Table
{
private:
	unsigned tableSize;
	unsigned firstEmpty;
	TableKey* tableKeyList;
	bool KeysAreSorted() const;
	void FindFirstEmpty();
public:
	Table(const Table& T);
	Table(unsigned size);
	~Table();
	void AllocateRows(unsigned newRowsCount);
	//Table& operator[](unsigned key);
	const TableKey& operator[](unsigned key) const;
	void PrintTable(std::ostream& os = std::cout) const;
	void TableAdd(const TableKey* keyAndValue);
	void TableAdd(int key, int intValue, const std::string& stringValue);
	bool IsFull() const;
	void SortKeys();
};