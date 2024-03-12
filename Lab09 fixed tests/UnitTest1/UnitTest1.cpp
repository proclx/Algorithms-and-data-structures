#include "pch.h"
#include "CppUnitTest.h"
#include "../Project19/Set.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(OneItemMethods)
	{
	public:
		TEST_METHOD(AddItem)
		{
			Set A;
			Assert::IsFalse(A.ItemIsInSet('a'));
			Assert::IsFalse(A.ItemIsInSet('A'));
			A.Add('a');
			A.Add('A');
			Assert::IsTrue(A.ItemIsInSet('a'));
			Assert::IsTrue(A.ItemIsInSet('A'));
			Assert::IsFalse(A.ItemIsInSet('b'));
		}
		TEST_METHOD(RemoveItem)
		{
			Set A;
			Assert::IsFalse(A.ItemIsInSet('a'));
			A.Add('a');
			Assert::IsTrue(A.ItemIsInSet('a'));
			A.Remove('a');
			Assert::IsFalse(A.ItemIsInSet('a'));
		}
	};
	TEST_CLASS(MethodsWithSetsAsParam)
	{
	public:
		TEST_METHOD(AddSet)
		{
			Set A;
			A.Add('a');
			A.Add('A');
			Set B;
			B.AddSet(A);
			Assert::IsTrue(B.ItemIsInSet('a'));
			Assert::IsTrue(B.ItemIsInSet('A'));
		}
		TEST_METHOD(RemoveSet)
		{
			Set A;
			A.Add('a');
			A.Add('A');
			Set B;
			B.AddSet(A);
			Assert::IsTrue(B.ItemIsInSet('a'));
			Assert::IsTrue(B.ItemIsInSet('A'));
			B.RemoveSet(A);
			Assert::IsFalse(B.ItemIsInSet('a'));
			Assert::IsFalse(B.ItemIsInSet('A'));
		}
		TEST_METHOD(Insertion)
		{
			Set A;
			A.Add('a');
			A.Add('A');
			Set B;
			B.Add('a');
			Set InsertionSet = A.Intersection(B);
			Assert::IsTrue(InsertionSet.ItemIsInSet('a'));
			Assert::IsFalse(InsertionSet.ItemIsInSet('A'));
		}
	};
}
