#include "SparseMatrix.h"
#include <iostream>
#include <sstream>

int main()
{
	SparseMatrix<int> matrix{3, 3};

	matrix.Add(0, 2, 1);
	matrix.Add(0, 0, 1);
	matrix.Add(0, 1, 1);

	matrix.Print();
	std::ostringstream oss;
	matrix.Print(oss);
	std::cout << oss.str() << std::endl;

	/*try
	{
		std::cout << std::boolalpha << matrix.Has(0, 0) << ' ' << matrix.Has(1, 0) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		matrix.Add(0, 0, 2);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}*/

	//std::cout << std::boolalpha << matrix.Get(0, 0);

	return 0;
}