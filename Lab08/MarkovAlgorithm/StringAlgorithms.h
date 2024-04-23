#pragma once
#include <string>
#include <iostream>

class Formula
{
private:
	std::string left;
	std::string right;
public:
	Formula(std::string l = "", std::string r = "")
		: left(l), right(r)
	{
	}
	~Formula()
	{
	}
	std::string GetLeft() const
	{
		return left;
	}
	std::string GetRight() const
	{
		return right;
	}
};

int Find(const std::string& str, const std::string& in);
void Replace(std::string& in, const Formula& F);
void MarkovAlgorithm(std::string& in, const Formula* formulas, unsigned n);