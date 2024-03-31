#include "pch.h"
#include "CppUnitTest.h"
#include "../HashTable/HashTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(CreateHashTable)
		{
			HashTable<std::string> A;
			Assert::IsTrue(A.IsEmpty());
			A.Add("key", "value");
			Assert::IsFalse(A.IsEmpty());
		}
		TEST_METHOD(AddAndHas)
		{
			HashTable<std::string> A;
			Assert::IsFalse(A.Has("key"));
			A.Add("key", "value");
			Assert::IsTrue(A.Has("key"));
		}
		TEST_METHOD(Remove)
		{
			HashTable<std::string> A{1};
			Assert::IsFalse(A.Has("key"));
			A.Add("key", "value");
			A.Add("key1", "value");
			A.Add("key2", "value");
			Assert::IsTrue(A.Has("key"));
			Assert::IsTrue(A.Has("key1"));
			Assert::IsTrue(A.Has("key2"));
			Assert::IsFalse(A.IsEmpty());
			A.Remove("key");
			A.Remove("key1");
			A.Remove("key2");
			Assert::IsFalse(A.Has("key"));
			Assert::IsFalse(A.Has("key1"));
			Assert::IsFalse(A.Has("key2"));
			Assert::IsTrue(A.IsEmpty());
		}
		TEST_METHOD(Resize)
		{
			HashTable<std::string> A{ 1 };
			A.Add("key", "value");
			A.Add("key1", "value");
			A.Add("key2", "value");
			Assert::IsTrue(A.Has("key"));
			Assert::IsTrue(A.Has("key1"));
			Assert::IsTrue(A.Has("key2"));
			A.Resize(3);
			Assert::IsTrue(A.Has("key"));
			Assert::IsTrue(A.Has("key1"));
			Assert::IsTrue(A.Has("key2"));
		}
		TEST_METHOD(Operator)
		{
			HashTable<std::string> A;
			A.Add("key", "value");
			A.Add("key1", "value1");
			A.Add("key2", "value2");
			Assert::AreEqual(A["key"], std::string("value"));
			Assert::AreEqual(A["key1"], std::string("value1"));
			Assert::AreEqual(A["key2"], std::string("value2"));
			A["key"] = "anotherValue";
			Assert::AreEqual(A["key"], std::string("anotherValue"));
		}
		TEST_METHOD(Exceptions)
		{
			HashTable<std::string> A;
			A.Add("key", "value");
			// adding the same key
			try
			{
				A.Add("key", "value");
				Assert::IsTrue(false);
			}
			catch (const std::exception&)
			{
				Assert::IsTrue(true);
			}
			// removing key which doesnt exist
			try
			{
				A.Remove("this key does not exist");
				Assert::IsTrue(false);
			}
			catch (const std::exception&)
			{
				Assert::IsTrue(true);
			}
		}
	};
}
