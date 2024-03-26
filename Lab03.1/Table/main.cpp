#include "Table.h"
#include <string>
#include <iostream>
int main()
{
	system("pause");
	Table <double, std::string>& table = *new Table<double, std::string>();
	table.Add(101, "Luca").Add(105, "Sofia").Add(100, "Giovanni").Add(99, "Anna").Add(110, "Marco").Add(109, "Alessandra");
	std::cout << std::endl;
	table.PrintTable();
	table.Remove(105);
	std::cout << std::endl;
	table.PrintTable();
	table.Add(104, "John");
	std::cout << std::endl;
	table.PrintTable();
	try
	{
		table.Remove(1);
	}
	catch (const std::exception& e)
	{
		std::cout << std::endl;
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;
	table.~Table();
	return 0;
}