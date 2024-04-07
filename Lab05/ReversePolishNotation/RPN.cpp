#include "RPN.h"

bool IsOperand(char op)
{
	return (('0' <= op && op <= '9') || op == 'e' || op == 'p');
}

bool IsOperator(char op)
{
	return (op == '/' || op == '*' || op == '+' || op == '-' || op == '^');
}

bool IsOpeningBracket(char op)
{
	return (op == '(');
}

bool IsClosingBracket(char op)
{
	return (op == ')');
}

unsigned GetPriority(char op)
{
	switch (op)
	{
	case '(':
		return 4;
	case '^':
		return 3;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 2;
		break;
	case '+':
		return 1;
		break;
	case '-':
		return 1;
		break;
	default:
		throw(std::runtime_error("Can't distinguish operator priority"));
		break;
	}
}

std::string ToRPN(const std::string& expression, std::ostream& os)
{
	std::stack<char> operators;
	std::string result = "";

	double firstOperand = 0;
	double secondOperand = 0;

	for (unsigned i = 0; i < expression.size(); ++i)
	{
		if (IsOperand(expression[i]))
		{
			os << "Operand " << expression[i] << " adding to final expression\n";
			result += expression[i];
		}
		else if (IsOpeningBracket(expression[i]))
		{
			os << "Is opening bracket, pushing to the stack\n";
			operators.push(expression[i]);
		}
		else if (IsClosingBracket(expression[i]))
		{
			os << "Is closing bracket, poping all items till (\n";
			while (!operators.empty() && !IsOpeningBracket(operators.top()))
			{
				os << "Pushing " << operators.top() << " to final expression\n";
				result += operators.top();
				operators.pop();
			}
			if (operators.empty())
			{
				throw(std::runtime_error("No opening bracket found"));
			}
			else if (IsOpeningBracket(operators.top()))
			{
				operators.pop();
			}
		}
		else if (IsOperator(expression[i]))
		{
			while (!operators.empty() && !IsOpeningBracket(operators.top()) && (GetPriority(operators.top()) >= GetPriority(expression[i])))
			{
				result += operators.top();
				operators.pop();
			}
			operators.push(expression[i]);
		}
		else
		{
			throw(std::runtime_error(std::string("Unknown symbol ") + expression[i]));
		}
		os << "\nExpression on this stage: " << result << "\nStack on this stage: ";
		for (unsigned i = 0; i < operators.size(); ++i)
		{
			os << operators._Get_container()[i] << ' ';
		}
		os << '\n';
	}
	while (!operators.empty())
	{
		result += operators.top();
		operators.pop();
		os << "\nExpression on this stage: " << result << "\nStack on this stage: ";
		for (unsigned i = 0; i < operators.size(); ++i)
		{
			os << operators._Get_container()[i] << ' ';
		}
		os << '\n';
	}
	return result;
}

double CharToDouble(char op)
{
	if (op == 'e')
	{
		return EULER;
	}
	else if (op == 'p')
	{
		return PI;
	}
	return op - '0';
}

double Calculate(const std::string& expression)
{
	std::stack<double> operands;
	for (unsigned i = 0; i < expression.size(); ++i)
	{
		if (IsOperand(expression[i]))
		{
			operands.push(CharToDouble(expression[i]));
		}
		else if (IsOperator(expression[i]))
		{
			double firstOperand = operands.top();
			operands.pop();
			double secondOperand = operands.top();
			operands.pop();
			switch (expression[i])
			{
			case '+':
				operands.push(firstOperand + secondOperand);
				break;
			case '-':
				operands.push(secondOperand - firstOperand);
				break;
			case '*':
				operands.push(firstOperand * secondOperand);
				break;
			case '/':
				operands.push(secondOperand / firstOperand);
				break;
			case '^':
				operands.push(pow(secondOperand, firstOperand));
				break;
			default:
				break;
			}
		}
	}
	return operands.top();
}