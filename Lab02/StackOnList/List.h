#pragma once
struct List
{
public:
	List* list_next;
	int list_element;
	List(int value, List* next = nullptr)
		: list_next(next), list_element(value)
	{

	}
};