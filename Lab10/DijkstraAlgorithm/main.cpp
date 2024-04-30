#include <iostream>
#include "DijkstraAlgorithm.h"

int main()
{
	Graph G{ 6 };

	G.AddEdge(0, 1, 7);
	G.AddEdge(0, 2, 9);
	G.AddEdge(0, 5, 14);
	G.AddEdge(1, 2, 10);
	G.AddEdge(1, 3, 15);
	G.AddEdge(2, 3, 11);
	G.AddEdge(2, 5, 2);
	G.AddEdge(3, 4, 6);
	G.AddEdge(4, 5, 9);

	G.Print();

	std::vector<unsigned> distance;
	std::vector<unsigned> parent;
	std::vector<unsigned> path = DijkstraAlgorithm(G, 0, 4, distance, parent);
	std::cout << "All route size: " << FindRouteWeight(G, path) << std::endl;
	PrintRoute(path);
	return 0;
}

unsigned Sum(const std::vector<unsigned>& v)
{
	unsigned result = 0;
	for (unsigned i = 0; i < v.size(); ++i)
	{
		result += v[i];
	}
	return result;
}

unsigned FindRouteWeight(const Graph& G, const std::vector<unsigned>& path)
{
	unsigned result = 0;
	for (unsigned i = 0; i < path.size() - 1; ++i)
	{
		AbjListNode* curr = G[path[i]];
		while (curr->destination != path[i + 1])
		{
			curr = curr->next;
		}
		result += curr->weight;
	}
	return result;
}

void PrintRoute(const std::vector<unsigned>& route, std::ostream& os)
{
	for (unsigned i = 0; i < route.size() - 1; ++i)
	{
		if (route[i] == _INFINITY_)
		{
			os << "X -> ";
		}
		else
		{
			os << route[i] + 1 << " -> ";
		}
	}
	os << route[route.size() - 1] << '\n';
}

std::vector<unsigned> DijkstraAlgorithm(Graph& G, unsigned start, unsigned end, std::vector<unsigned>& d, std::vector<unsigned>& p)
{
	unsigned V = G.GetSize();
	std::vector<unsigned> distance(V, _INFINITY_);
	std::vector<unsigned> parent(V, _INFINITY_);
	std::vector<bool> processed(V, false);

	distance[start] = 0;

	for (unsigned count = 0; count < V - 1; ++count)
	{
		unsigned u = FindMinDistance(distance, processed, V);
		processed[u] = true;

		AbjListNode* curr = G[u];
		while (curr != nullptr)
		{
			unsigned v = curr->destination;
			unsigned weight = curr->weight;
			if (!processed[v] && distance[u] != _INFINITY_ && distance[u] + weight < distance[v])
			{
				distance[v] = distance[u] + weight;
				parent[v] = u;
			}
			curr = curr->next;
		}
	}
	std::vector<unsigned> path;
	unsigned crawl = end;
	while (crawl != _INFINITY_ && crawl != start)
	{
		path.push_back(crawl);
		crawl = parent[crawl];
	}
	if (crawl == start)
	{
		path.push_back(start);
	}
	std::reverse(path.begin(), path.end());
	d = distance;
	p = parent;
	return path;
}

unsigned FindMinDistance(const std::vector<unsigned>& distance, const std::vector<bool>& processed, unsigned V)
{
	unsigned minDistance = _INFINITY_;
	unsigned minIndex;
	for (unsigned v = 0; v < V; v++)
	{
		if (!processed[v] && distance[v] <= minDistance)
		{
			minDistance = distance[v];
			minIndex = v;
		}
	}
	return minIndex;
}