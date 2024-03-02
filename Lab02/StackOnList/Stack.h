#pragma once
#include "List.h"
class Stack
{
private:
	List* stackTop;
public:
	Stack()
		: stackTop(nullptr)
	{

	}
	Stack(const Stack& other)
	{
		this->~Stack();
		if (other.stackTop != nullptr)
		{
			List* toCopy = other.stackTop;
			stackTop = new List(toCopy->list_element);
			List* stackTopCurr = stackTop;
			toCopy = toCopy->list_next;
			while (toCopy != nullptr)
			{
				stackTopCurr->list_next = new List(toCopy->list_element);
				stackTopCurr = stackTopCurr->list_next;
				toCopy = toCopy->list_next;
			}
		}
	}
	~Stack()
	{
		while (stackTop != nullptr)
		{
			List* victim = stackTop;
			stackTop = stackTop->list_next;
			delete victim;
		}
		stackTop = nullptr;
	}
	void Push(int value)
	{
		// new List(value) -> [stackTop]
		List* newTop = new List(value, stackTop);
		stackTop = newTop;
	}
	int Pop()
	{
		int result = stackTop->list_element;
		List* temp = stackTop;
		stackTop = stackTop->list_next;
		delete temp;
		return result;
	}
	bool IsEmpty()
	{
		return stackTop == nullptr;
	}
};