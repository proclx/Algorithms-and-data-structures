#include <iostream>
#include "StringAlgorithms.h"

void UnaryMultiplication(std::string& unaryExpression)
{
	const unsigned n = 8;
	Formula* unaryMultiplicationRules = new Formula[n];
	unaryMultiplicationRules[0] = { "|b", "ba|" };
	unaryMultiplicationRules[1] = { "ab", "ba" };
	unaryMultiplicationRules[2] = { "b", "" };
	unaryMultiplicationRules[3] = { "*|", "b*" };
	unaryMultiplicationRules[4] = { "*", "c" };
	unaryMultiplicationRules[5] = { "|c", "c" };
	unaryMultiplicationRules[6] = { "ac", "c|" };
	unaryMultiplicationRules[7] = { "c", "" };

	MarkovAlgorithm(unaryExpression, unaryMultiplicationRules, n);
}

void BinaryToUnary(std::string& binary)
{
	const unsigned n = 3;
	Formula* binaryToUnaryRules = new Formula[n];
	binaryToUnaryRules[0] = { "|0", "0||" };
	binaryToUnaryRules[1] = { "1", "0|" };
	binaryToUnaryRules[2] = { "0", "" };

	MarkovAlgorithm(binary, binaryToUnaryRules, n);
}

int main()
{
	std::string unaryExpression{ "||*|||" };
	UnaryMultiplication(unaryExpression);
	std::cout << unaryExpression << std::endl;

	return 0;
}