#include <iostream>
#include "HashTable.h"
#include <string>

int main()
{
	HashTable<std::string> table(3);
	table.Add("Matteo", "Rossi").Add("Giulia", "Bianchi").Add("Francesco", "Marcello").Add("Alessia", "Giovanni").Add("Lorenzo", "Romano");
	table.PrintTable();
	std::cout << std::boolalpha << table.Has("Matteo") << '\n' << table.Has("Rossi") << std::endl;
	try
	{
		table.Add("Matteo", "Rossi");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	HashTable<std::string> tableCopy{ table };
	tableCopy.PrintTable();
	std::cout << (&tableCopy["Matteo"] != &table["Matteo"]) << std::endl;
	tableCopy.Resize(10);
	std::cout << "Resized table:\n";
	tableCopy.PrintTable();
	table.Remove("Matteo");
	std::cout << std::endl;
	table.PrintTable();
	std::cout << table.Has("Matteo");
	return 0;
}
