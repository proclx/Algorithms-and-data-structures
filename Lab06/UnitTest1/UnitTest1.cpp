#include <iostream>
#include <sstream>
#include "pch.h"
#include "CppUnitTest.h"
#include "../SparseMatrix/SparseMatrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Add)
		{
			SparseMatrix<int> matrix{3, 3};
			Assert::IsFalse(matrix.Has(0, 0));
			Assert::IsFalse(matrix.Has(0, 1));
			Assert::IsFalse(matrix.Has(0, 2));
			matrix.Add(0, 2, 1);
			matrix.Add(0, 0, 1);
			matrix.Add(0, 1, 1);
			Assert::IsTrue(matrix.Has(0, 1));
			Assert::IsTrue(matrix.Has(0, 2));
			Assert::IsTrue(matrix.Has(0, 0));
		}
		TEST_METHOD(Remove)
		{
			SparseMatrix<int> matrix{ 3, 3 };
			matrix.Add(0, 2, 1);
			matrix.Add(0, 0, 1);
			matrix.Add(0, 1, 1);
			Assert::IsTrue(matrix.Has(0, 1));
			Assert::IsTrue(matrix.Has(0, 2));
			Assert::IsTrue(matrix.Has(0, 0));
			matrix.Remove(0, 1);
			matrix.Remove(0, 2);
			matrix.Remove(0, 0);
			Assert::IsFalse(matrix.Has(0, 0));
			Assert::IsFalse(matrix.Has(0, 1));
			Assert::IsFalse(matrix.Has(0, 2));
		}
		TEST_METHOD(Get)
		{
			SparseMatrix<int> matrix{ 3, 3 };
			matrix.Add(0, 0, 1);
			matrix.Add(0, 1, 1);
			Assert::AreEqual(matrix.Get(0, 0), 1);
			Assert::AreEqual(matrix.Get(0, 1), 1);
			matrix.Get(0, 0) = 2;
			matrix.Get(0, 1) = 3;
			Assert::AreEqual(matrix.Get(0, 0), 2);
			Assert::AreEqual(matrix.Get(0, 1), 3);
		}
		TEST_METHOD(Print)
		{
			SparseMatrix<int> matrix{ 3, 3 };
			matrix.Add(0, 2, 1);
			matrix.Add(0, 0, 1);
			matrix.Add(0, 1, 1);
			std::ostringstream oss;
			matrix.Print(oss);
			Assert::AreEqual(oss.str(), (std::string)"1 1 1 \n0 0 0 \n0 0 0 \n");
		}
	};
}
