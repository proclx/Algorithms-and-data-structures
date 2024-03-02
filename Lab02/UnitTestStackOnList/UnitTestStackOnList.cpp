#include "pch.h"
#include "CppUnitTest.h"
#include "../StackOnList/List.h"
#include "../StackOnList/Stack.h"
#include <stack>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestStackOnList
{
	TEST_CLASS(UnitTestStackOnList)
	{
	public:
		TEST_METHOD(StackIsEmpty)
		{
			Stack stack;
			Assert::IsTrue(stack.IsEmpty());
			stack.Push(0);
			Assert::IsFalse(stack.IsEmpty());
			stack.Pop();
			Assert::IsTrue(stack.IsEmpty());
		}
		TEST_METHOD(StackPushPop)
		{
			Stack stack;
			stack.Push(1);
			stack.Push(2);
			stack.Push(3);
			Assert::AreEqual(stack.Pop(), 3);
			Assert::AreEqual(stack.Pop(), 2);
			Assert::AreEqual(stack.Pop(), 1);
			Assert::IsTrue(stack.IsEmpty());
		}
		TEST_METHOD(DeleteStack)
		{
			Stack stack;
			stack.Push(1);
			stack.Push(2);
			stack.Push(3);
			stack.~Stack();
			Assert::IsTrue(stack.IsEmpty());
		}
		TEST_METHOD(StackCopyConstructor)
		{
			Stack stackA;
			stackA.Push(1);
			stackA.Push(2);
			Stack stackB(stackA);
			Assert::AreEqual(stackA.Pop(), 2);
			Assert::AreEqual(stackA.Pop(), 1);

			Assert::IsTrue(stackA.IsEmpty());
			Assert::IsFalse(stackB.IsEmpty());

			Assert::AreEqual(stackB.Pop(), 2);
			Assert::AreEqual(stackB.Pop(), 1);

			Assert::IsTrue(stackB.IsEmpty());
		}
		TEST_METHOD(TheSameAsSTLStack)
		{
			std::stack<int> STLStack;
			Stack myStack;
			Assert::AreEqual(STLStack.empty(), myStack.IsEmpty());
			STLStack.push(1);
			myStack.Push(1);
			STLStack.push(2);
			myStack.Push(2);
			Assert::AreEqual(STLStack.top(), myStack.Pop());
			STLStack.pop();
			Assert::AreEqual(STLStack.top(), myStack.Pop());
			STLStack.pop();
			Assert::AreEqual(STLStack.empty(), myStack.IsEmpty());
		}
	};
}
