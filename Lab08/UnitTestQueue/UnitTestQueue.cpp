#include "pch.h"
#include "CppUnitTest.h"
#include "../Queue/Queue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestQueue
{
	TEST_CLASS(UnitTestQueue)
	{
	public:
		TEST_METHOD(QueueIsEmpty)
		{
			Queue Q;
			Assert::IsTrue(Q.IsEmpty());
			Q.Push(1);
			Assert::IsFalse(Q.IsEmpty());
			Q.Pop();
			Assert::IsTrue(Q.IsEmpty());
		}
		TEST_METHOD(QueuePushPop)
		{
			Queue Q;
			Q.Push(1);
			Q.Push(2);
			Q.Push(3);
			Assert::AreEqual(Q.Pop(), 1);
			Assert::AreEqual(Q.Pop(), 2);
			Assert::AreEqual(Q.Pop(), 3);
			Assert::IsTrue(Q.IsEmpty());
		}
		TEST_METHOD(QueueCopy)
		{
			Queue Q;
			Q.Push(1);
			Q.Push(2);
			Q.Push(3);
			Queue copy(Q);
			Assert::AreEqual(Q.Pop(), 1);
			Assert::AreEqual(Q.Pop(), 2);
			Assert::AreEqual(Q.Pop(), 3);
			Assert::IsTrue(Q.IsEmpty());
			Assert::AreEqual(copy.Pop(), 1);
			Assert::AreEqual(copy.Pop(), 2);
			Assert::AreEqual(copy.Pop(), 3);
			Assert::IsTrue(copy.IsEmpty());
		}
	};
	TEST_CLASS(UnitTestPriorityQueue)
	{
	public:
		TEST_METHOD(PriorityQueueIsEmpty)
		{
			PriorityQueue PQ(3);
			Assert::IsTrue(PQ.IsEmpty());
			PQ.Push(2, 1);
			Assert::IsFalse(PQ.IsEmpty());
			PQ.Pop();
			Assert::IsTrue(PQ.IsEmpty());
		}
		TEST_METHOD(PriorityQueuePushPop)
		{
			PriorityQueue PQ;
			PQ.Push(1, 2);
			PQ.Push(3, 1);
			PQ.Push(2, 2);
			PQ.Push(4, 1);
			Assert::AreEqual(PQ.Pop(), 3);
			Assert::AreEqual(PQ.Pop(), 4);
			Assert::AreEqual(PQ.Pop(), 1);
			Assert::AreEqual(PQ.Pop(), 2);
			Assert::IsTrue(PQ.IsEmpty());
		}
		TEST_METHOD(PriorityQueueChangeMaxPriority)
		{
			PriorityQueue PQ;
			PQ.Push(1, 2);
			PQ.Push(3, 1);
			PQ.Push(2, 2);
			PQ.Push(4, 1);
			PQ.ChangeMaxPriority(4);
			PQ.Push(5, 3);
			PQ.Push(6, 1);
			Assert::AreEqual(PQ.Pop(), 3);
			Assert::AreEqual(PQ.Pop(), 4);
			Assert::AreEqual(PQ.Pop(), 6);
			Assert::AreEqual(PQ.Pop(), 1);
			Assert::AreEqual(PQ.Pop(), 2);
			Assert::AreEqual(PQ.Pop(), 5);
			Assert::IsTrue(PQ.IsEmpty());
		}
	};
}
