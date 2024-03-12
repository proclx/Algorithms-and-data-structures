#include "Set.h"

Set::~Set()
{
}

Set::Set()
{
	for (unsigned i = 0; i < CHAR_NUMBER_OF_ALL_VALUES / INT_NUMBER_OF_BITS; ++i)
	{
		intArray[i] = 0;
	}
}

Set::Set(const Set& set)
{
	for (unsigned i = 0; i < CHAR_NUMBER_OF_ALL_VALUES / INT_NUMBER_OF_BITS; ++i)
	{
		intArray[i] = set.intArray[i];
	}
}

void Set::Add(unsigned char item)
{
	unsigned index;
	index = item % INT_NUMBER_OF_BITS;
	unsigned mask = 1 << index;
	intArray[item / INT_NUMBER_OF_BITS] |= mask;
}

void Set::Remove(unsigned char item)
{
	unsigned index;
	index = item % INT_NUMBER_OF_BITS;
	unsigned mask = 1 << index;
	intArray[item / INT_NUMBER_OF_BITS] &= ~mask;
}

void Set::AddSet(const Set& set)
{
	for (unsigned i = 0; i < CHAR_NUMBER_OF_ALL_VALUES / INT_NUMBER_OF_BITS; ++i)
	{
		intArray[i] |= set.intArray[i];
	}
}

void Set::RemoveSet(const Set& set)
{
	for (unsigned i = 0; i < CHAR_NUMBER_OF_ALL_VALUES / INT_NUMBER_OF_BITS; ++i)
	{
		intArray[i] &= ~set.intArray[i];
	}
}

bool Set::ItemIsInSet(unsigned char item) const
{
	unsigned index;
	index = item % INT_NUMBER_OF_BITS;
	unsigned mask = 1 << index;
	bool result = intArray[item / INT_NUMBER_OF_BITS] & mask;
	return result;
}

Set& Set::Intersection(const Set& set) const
{
	Set& result = *new Set();
	for (unsigned i = 0; i < CHAR_NUMBER_OF_ALL_VALUES / INT_NUMBER_OF_BITS; ++i)
	{
		result.intArray[i] = set.intArray[i] & intArray[i];
	}
	return result;
}

void Set::PrintSet() const
{
	for (unsigned i = 0; i < CHAR_NUMBER_OF_ALL_VALUES / INT_NUMBER_OF_BITS; ++i)
	{
		unsigned mask = 1;
		for (unsigned j = 0; j < INT_NUMBER_OF_BITS; ++j)
		{
			if (intArray[i] & mask)
			{
				std::cout << char(i * INT_NUMBER_OF_BITS + j) << ' ';
			}
			mask = mask << 1;
		}
	}
	std::cout << std::endl;
}
