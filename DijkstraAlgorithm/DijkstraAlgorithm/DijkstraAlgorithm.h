#pragma once
#include <vector>
#include <iostream>

const unsigned _INFINITY_ = -1;

// graph representation in current implementation
/*

Graph
int v
AbjList* l 
	[0] = head (AbjListNode*) -> Node(weight, destination) -> Node(weight, destination) -> ... -> Node(weight, destination)
	[1]
	...
	[v-1]
*/

struct AbjListNode
{
public:
	unsigned weight;
	unsigned destination;
	AbjListNode* next;

	AbjListNode(unsigned w, unsigned d)
		: weight(w), destination(d), next(nullptr)
	{
	}
};

struct AbjList
{
public:
	AbjListNode* head;

	AbjList()
		: head(nullptr)
	{
	}
	~AbjList()
	{
		AbjListNode* curr = head;
		while (curr != nullptr)
		{
			AbjListNode* toDelete = curr;
			curr = curr->next;
			delete toDelete;
		}
		head = nullptr;
	}
	void PrintAbjList(std::ostream& os = std::cout) const
	{
		AbjListNode* curr = head;
		while (curr != nullptr)
		{
			os << curr->destination << " (" << curr->weight << ") -> ";
			curr = curr->next;
		}
		os << "nullptr\n";
	}
	void AddEdge(AbjListNode* toInsert)
	{
		if (head == nullptr)
		{
			head = toInsert;
		}
		else
		{
			AbjListNode* curr = head;
			while (curr->next != nullptr)
			{
				if (curr->destination == toInsert->destination && curr->weight == toInsert->weight)
				{
					return;
				}
				curr = curr->next;
			}
			curr->next = toInsert;
		}
	}
	void AddEdge(unsigned destination, unsigned weight)
	{
		if (head == nullptr)
		{
			head = new AbjListNode(weight, destination);
		}
		else
		{
			AbjListNode* curr = head;
			while (curr->next != nullptr)
			{
				if (curr->destination == destination && curr->weight == weight)
				{
					return;
				}
				curr = curr->next;
			}
			curr->next = new AbjListNode(weight, destination);
		}
	}
};

class Graph
{
private:
	unsigned numberOfVertices;
	AbjList* list;
public:
	Graph(const Graph& G) = delete;
	Graph(unsigned v)
		: numberOfVertices(v)
	{
		list = new AbjList[v];
	}
	virtual ~Graph()
	{
		delete[] list;
	}
	void Print(std::ostream& os = std::cout) const
	{
		for (unsigned i = 0; i < numberOfVertices; ++i)
		{
			os << "vertical[" << i << "] -> ";
			list[i].PrintAbjList(os);
		}
	}
	void AddEdge(unsigned sourse, unsigned destination, unsigned weight)
	{
		list[sourse].AddEdge(new AbjListNode(weight, destination));
		list[destination].AddEdge(new AbjListNode(weight, sourse));
	}
	AbjListNode* operator[](unsigned n) const
	{
		return list[n].head;
	}
	unsigned GetSize() const
	{
		return numberOfVertices;
	}
};

template<typename T>
bool SameRoutes(const std::vector<T>& v1, const std::vector<T>& v2)
{
	if (v1.size() != v2.size())
	{
		return false;
	}
	else
	{
		for (unsigned i = 0; i < v1.size(); ++i)
		{
			if (v1[i] != v2[i])
			{
				return false;
			}
		}
		return true;
	}
}

unsigned FindMinDistance(const std::vector<unsigned>& distance, const std::vector<bool>& processed, unsigned V);
std::vector<unsigned> DijkstraAlgorithm(Graph& G, unsigned start, unsigned end, std::vector<unsigned>& d, std::vector<unsigned>& p);
void PrintRoute(const std::vector<unsigned>& route, std::ostream& os = std::cout);
unsigned Sum(const std::vector<unsigned>& v);
unsigned FindRouteWeight(const Graph& G, const std::vector<unsigned>& path);