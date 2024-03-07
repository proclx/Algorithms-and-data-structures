#include "Table.h"

int main()
{
	Table firstTable{ 10 };
	firstTable.TableAdd(100, 17, "Ivan");
	firstTable.TableAdd(101, 18, "Mia");
	firstTable.PrintTable();
	firstTable.IsFull();
	
	return 0;
}