#include <string>
#include "pch.h"
#include "CppUnitTest.h"
#include "../MarkovAlgorithm/StringAlgorithms.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MarkovTest
{
	TEST_CLASS(StringAlgorithms)
	{
	public:
		TEST_METHOD(_Find)
		{
			std::string abc{ "abc" };
			std::string abacabcad{ "abacabcad" };
			Assert::AreEqual(Find(abc, abacabcad), 4);

			std::string a{ "a" };
			std::string bcd{ "bcd" };
			Assert::AreEqual(Find(a, bcd), -1);

			std::string ab{ "ab" };
			std::string aaabbb{ "aaabbb" };
			Assert::AreEqual(Find(ab, aaabbb), 2);

			std::string abcd{ "abcd" };
			std::string abcda{ "abcda" };
			Assert::AreEqual(Find(abcd, abcda), 0);

			std::string dc{ "dc" };
			std::string abdcda{ "abdcda" };
			Assert::AreEqual(Find(dc, abdcda), 2);

			std::string ababcab{ "ababcab" };
			Assert::AreEqual(Find(abc, ababcab), 2);
		}
		TEST_METHOD(_Replace)
		{
			Formula formula{ "ab", "c" };
			std::string ababac{ "ababac" };
			std::string ccac{ "ccac" };
			Replace(ababac, formula);
			Assert::AreEqual(ababac, ccac);

			std::string ab{ "ab" };
			std::string c{ "c" };
			Replace(ab, formula);
			Assert::AreEqual(ab, c);
		}
		TEST_METHOD(_Markov_unary_multiplication)
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

			std::string unaryExpression{ "||*|||" };
			MarkovAlgorithm(unaryExpression, unaryMultiplicationRules, n);

			Assert::AreEqual(unaryExpression, std::string("||||||"));
		}
		TEST_METHOD(_Markov_binary_to_unary)
		{
			const unsigned n = 3;
			Formula* binaryToUnaryRules = new Formula[n];
			binaryToUnaryRules[0] = { "|0", "0||" };
			binaryToUnaryRules[1] = { "1", "0|" };
			binaryToUnaryRules[2] = { "0", "" };

			std::string nine{ "1001" };
			MarkovAlgorithm(nine, binaryToUnaryRules, n);
			Assert::AreEqual(nine, std::string("|||||||||"));
		}
	};
}
