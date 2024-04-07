#include "pch.h"
#include "CppUnitTest.h"
#include "../ReversePolishNotation/RPN.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(CorrectNotation)
	{
	public:
		TEST_METHOD(CorrectPriority)
		{
			std::string expression{ "(2+4)/(3+(2*3))/4*(2*(3*4))" };
			std::string correctExpression{ "24+323*+/4/234***" };
			Assert::AreEqual(ToRPN(expression), correctExpression);
		}
		TEST_METHOD(PI_AND_EULER)
		{
			std::string expression{ "p+e" };
			std::string correctExpression{ "pe+" };
			Assert::AreEqual(ToRPN(expression), correctExpression);
		}
		TEST_METHOD(ParenthesisParenthesisParenthesis)
		{
			std::string expression{ "(((3*4)*(2+3)))*(((((9+2)))))" };
			std::string correctExpression{ "34*23+*92+*" };
			Assert::AreEqual(ToRPN(expression), correctExpression);
		}
		TEST_METHOD(Pow)
		{
			std::string expression{ "3+4*2/((1-5)^2)^3" };
			std::string correctExpression{ "342*15-2^3^/+" };
			Assert::AreEqual(ToRPN(expression), correctExpression);
		}
		TEST_METHOD(WithError)
		{
			std::string expression{ "2+3)" };
			try
			{
				ToRPN(expression);
				Assert::IsTrue(false);
			}
			catch (const std::exception& e)
			{
				Assert::AreEqual(e.what(), "No opening bracket found");
			}
		}
	};
	TEST_CLASS(CalculateExpression)
	{
		TEST_METHOD(FirstTest)
		{
			std::string expression{ "(2+4)/(3+(2*3))/4*(2*(3*4))" };
			Assert::AreEqual(Calculate(ToRPN(expression)), 4.);
		}
		TEST_METHOD(SecondTest)
		{
			std::string expression{ "(((3*4)*(2+3)))*(((((9+2)))))" };
			Assert::AreEqual(Calculate(ToRPN(expression)), 660.);
		}
		TEST_METHOD(ThirdTest)
		{
			std::string expression{ "22+" };
			Assert::AreEqual(Calculate(ToRPN(expression)), 4.);
		}
		TEST_METHOD(PI_AND_EULER_Test)
		{
			std::string expression{ "p+e" };
			Assert::AreEqual((int)(Calculate(ToRPN(expression))*100), 585);
		}
	};
}
