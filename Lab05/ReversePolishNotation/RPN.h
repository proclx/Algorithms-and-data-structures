#pragma once
#include <string>
#include <stack>
#include <exception>
#include <cmath>
#include <iostream>
const double EULER = 2.71828182845904523536;
const double PI = 3.14159265358979323846;

bool IsOperand(char op);
bool IsOperator(char op);
bool IsOpeningBracket(char op);
bool IsClosingBracket(char op);
unsigned GetPriority(char op);
std::string ToRPN(const std::string& expression, std::ostream& os = std::cout);
double CharToDouble(char op);
double Calculate(const std::string& expression);