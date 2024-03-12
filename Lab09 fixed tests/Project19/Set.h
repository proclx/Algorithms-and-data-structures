#pragma once
#include <iostream>

const unsigned CHAR_NUMBER_OF_ALL_VALUES = 256;
const unsigned INT_NUMBER_OF_BITS = 32;

class Set
{
private:
	unsigned intArray[CHAR_NUMBER_OF_ALL_VALUES / INT_NUMBER_OF_BITS];
public:
	~Set();
	Set();
	Set(const Set& set);
	void Add(unsigned char item);
	void Remove(unsigned char item);
	void AddSet(const Set& set);
	void RemoveSet(const Set& set);
	bool ItemIsInSet(unsigned char item) const;
	Set& Intersection(const Set& set) const;
	void PrintSet() const;
};

