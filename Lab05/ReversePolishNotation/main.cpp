#include "RPN.h"

int main()
{
	std::string expression{ "2+2*2" };
	try
	{
		std::string result = ToRPN(expression, std::cout);
		std::cout << result << std::endl;
		std::cout << Calculate(result) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}