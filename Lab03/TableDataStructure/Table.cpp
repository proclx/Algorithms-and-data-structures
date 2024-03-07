#include "Table.h"
#include <iomanip>

bool TableKey::IsEmpty() const
{
	return value == nullptr;
}

TableValue* TableValue::Copy() const
{
	TableValue* result = new TableValue();
	result->intValue = intValue;
	result->stringValue = stringValue;
	return result;
}

int TableKey::GetKey() const
{
	return key;
}

void TableKey::Print(std::ostream& os) const
{
	os << std::setw(SET_W_PROPERTIES_FOR_KEY) << key
		<< std::setw(SET_W_PROPERTIES_FOR_INT_VALUE) << value->intValue
		<< std::setw(SET_W_PROPERTIES_FOR_STRING_VALUE) << value->stringValue
		<< std::endl;
}

TableKey::TableKey()
{
	key = 0;
	value = nullptr;
}

TableKey::~TableKey()
{
	delete value;
	value = nullptr;
}

TableValue::TableValue()
{
	intValue = 0;
	stringValue = "";
}

TableValue::TableValue(int value, const std::string& sValue)
	: intValue(value), stringValue(sValue)
{

}

void Table::FindFirstEmpty()
{
	for (unsigned i = 0; i < tableSize; ++i)
	{
		if (tableKeyList[i].IsEmpty())
		{
			firstEmpty = i;
			return;
		}
	}
	firstEmpty = tableSize;
}

Table::Table(const Table& T) // deep copy
{
	tableSize = T.tableSize;
	firstEmpty = T.firstEmpty;
	tableKeyList = new TableKey[tableSize];
	for (unsigned i = 0; i < tableSize; ++i)
	{
		tableKeyList->key = T.tableKeyList->key;
		tableKeyList->value = T.tableKeyList->value->Copy();
	}
}

Table::Table(unsigned size)
	: tableSize(size), firstEmpty(0), tableKeyList(new TableKey[size])
{
	for (unsigned i = 0; i < size; ++i)
	{
		tableKeyList[i].value = nullptr;
	}
}

Table::~Table()
{
	delete[] tableKeyList;
	std::cout << "Table was deleted\n";
}

const TableKey& Table::operator[](unsigned key) const
{
	for (unsigned i = 0; i < tableSize; ++i)
	{
		if (tableKeyList[i].key == key && !tableKeyList[i].IsEmpty())
		{
			return tableKeyList[i];
		}
	}
	throw("UnvalidKey\n");
}

void Table::PrintTable(std::ostream& os) const
{
	os << std::setw(SET_W_PROPERTIES_FOR_KEY) << "key"
		<< std::setw(SET_W_PROPERTIES_FOR_INT_VALUE) << "int"
		<< std::setw(SET_W_PROPERTIES_FOR_STRING_VALUE) << "string"
		<< std::endl;
	for (unsigned i = 0; i < tableSize; ++i)
	{
		if (tableKeyList[i].IsEmpty())
		{
			continue;
		}
		else
		{
			tableKeyList[i].Print(os);
		}
	}
}

void Table::TableAdd(const TableKey* keyAndValue)
{
	tableKeyList[firstEmpty].key = keyAndValue->key;
	tableKeyList[firstEmpty].value = keyAndValue->value->Copy();
	FindFirstEmpty();
}

void Table::TableAdd(int key, int intValue, const std::string& stringValue)
{
	tableKeyList[firstEmpty].key = key;
	tableKeyList[firstEmpty].value = new TableValue(intValue, stringValue);
	// we need to change firstEmpty
	FindFirstEmpty();
}

bool Table::IsFull() const
{
	return firstEmpty == tableSize;
}
