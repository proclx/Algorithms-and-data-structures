#include "pch.h"
#include "CppUnitTest.h"
#include "../Table/Table.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(EmptyTable)
		{
			Table<unsigned, std::string> table;
			//Assert::IsFalse(table.Has(0));
			try
			{
				table.Remove(0);
			}
			catch (const std::exception& e)
			{
				Assert::AreEqual(e.what(), "Table has no such value");
			}
		}
		TEST_METHOD(AddRecording)
		{
			Table<unsigned, std::string> table;
			table.Add(100, "Ivan");
			Assert::IsTrue(table.Has(100));
			Assert::IsFalse(table.Has(101));
			
		}
		TEST_METHOD(RemoveRecording)
		{
			Table<unsigned, std::string> table;
			table.Add(101, "Luca").Add(105, "Sofia").Add(100, "Giovanni").Add(99, "Anna").Add(110, "Marco");
			Assert::IsTrue(table.Has(101));
			Assert::IsTrue(table.Has(105));
			Assert::IsTrue(table.Has(100));
			Assert::IsTrue(table.Has(99));
			Assert::IsTrue(table.Has(110));
			table.Remove(101);
			table.Remove(100);
			table.Remove(110);
			Assert::IsFalse(table.Has(101));
			Assert::IsTrue(table.Has(105));
			Assert::IsFalse(table.Has(100));
			Assert::IsTrue(table.Has(99));
			Assert::IsFalse(table.Has(110));
		}
		TEST_METHOD(RemoveAndAdd)
		{
			Table<unsigned, std::string> table;
			table.Add(101, "Luca").Add(105, "Sofia").Add(100, "Giovanni").Add(99, "Anna").Add(110, "Marco").Add(109, "Margo");
			Assert::IsTrue(table.Has(110));
			table.Remove(110);
			Assert::IsTrue(table.Has(109));
			table.Add(108, "Mia");
			Assert::IsTrue(table.Has(108));
			Assert::IsFalse(table.Has(110));
		}
		TEST_METHOD(ChangeValue)
		{
			Table<unsigned, std::string> table;
			table.Add(101, "Luca");
			std::string prevValue = table[101];
			table[101] = "Not Luca";
			Assert::AreNotEqual(prevValue, table[101]);
		}
		TEST_METHOD(UncorrectKey)
		{
			Table<unsigned, std::string> table;
			table.Add(101, "Luca");
			try
			{
				table[100];
			}
			catch (const std::exception& e)
			{
				Assert::AreEqual(e.what(), "Table has no such value");
			}
		}
		TEST_METHOD(DeleteTable)
		{
			Table<unsigned, std::string> table;
			table.Add(101, "Luca").Add(102, "Ivan");
			Assert::IsTrue(table.Has(101));
			Assert::IsTrue(table.Has(102));
			table.~Table();
			Assert::IsFalse(table.Has(102));
		}
	};
}
