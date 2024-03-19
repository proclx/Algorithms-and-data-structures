#pragma once

struct List
{
public:
	List* next;
	int value;
	List(int val) : value(val), next(nullptr) 
	{
	}
};

class Queue
{
private:
	List* tail;
	List* head;
public:
	~Queue()
	{
		while (head != nullptr)
		{
			List* temp = head;
			head = head->next;
			delete temp;
		}
		head = nullptr;
		tail = nullptr;
	}
	Queue(int val)
	{
		head->value = val;
		tail = head;
		head = head;
	}
	Queue()
	{
		head = nullptr;
		tail = nullptr;
	}
	Queue(const Queue& Q)
	{
		if (Q.IsEmpty())
		{
			head = nullptr;
			tail = nullptr;
		}
		List* Q_iter = Q.head;
		head = new List(Q_iter->value);
		tail = head;
		while (Q_iter->next != nullptr)
		{
			Q_iter = Q_iter->next;
			tail->next = new List(Q_iter->value);
			tail = tail->next;
		}
	}
	void Push(int val)
	{
		if (IsEmpty())
		{
			head = new List(val);
			tail = head;
		}
		else
		{
			tail->next = new List(val);
			tail = tail->next;
		}
	}
	bool IsEmpty() const
	{
		return head == nullptr;
	}
	int Pop()
	{
		if (IsEmpty())
		{
			throw("Queue is empty");
		}
		else
		{
			int result;
			result = head->value;
			List* temp = head;
			if (head->next == nullptr)
			{
				head = nullptr;
			}
			else
			{
				head = head->next;
			}
			delete temp;
			return result;
		}
	}
};

class PriorityQueue
{
private:
	unsigned maxPriority;
	Queue** queues;
public:
	~PriorityQueue()
	{
		for (unsigned i = 0; i < maxPriority; ++i)
		{
			queues[i]->~Queue();
		}
		queues = nullptr;
	}
	PriorityQueue(unsigned levelOfPriority = 3) : maxPriority(levelOfPriority), queues(new Queue*[levelOfPriority])
	{
		for (unsigned i = 0; i < levelOfPriority; ++i)
		{
			queues[i] = new Queue();
		}
	}
	void Push(int val, unsigned priority)
	{
		queues[priority]->Push(val);
	}
	int Pop()
	{
		for (unsigned i = 0; i < maxPriority; ++i)
		{
			if (!queues[i]->IsEmpty())
			{
				return queues[i]->Pop();
			}
		}
		throw("Priority queue is empty");
	}
	bool IsEmpty() const
	{
		for (unsigned i = 0; i < maxPriority; ++i)
		{
			if (!queues[i]->IsEmpty())
			{
				return false;
			}
		}
		return true;
	}
	void ChangeMaxPriority(unsigned newPriority)
	{
		Queue** newQueue = new Queue*[newPriority];
		unsigned i = 0;
		for (; i < maxPriority; ++i)
		{
			newQueue[i] = queues[i];
		}
		for (; i < newPriority; ++i)
		{
			newQueue[i] = new Queue();
		}
		maxPriority = newPriority;
		queues = newQueue;
	}
};