#include "pch.h"
#include "CppUnitTest.h"
#include "../DijkstraAlgorithm/DijkstraAlgorithm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(_GraphAbjList_list_pointers_)
		{
			Graph G{ 3 };
			Assert::AreEqual(G.GetSize(), 3u);
			Assert::IsTrue(G[0] == nullptr);
			Assert::IsTrue(G[1] == nullptr);
			Assert::IsTrue(G[2] == nullptr);
			G.AddEdge(0, 1, 2);
			Assert::IsFalse(G[0] == nullptr);
			Assert::IsFalse(G[1] == nullptr);
			Assert::IsTrue(G[2] == nullptr);
			Assert::IsTrue(G[0]->next == nullptr);
			Assert::IsTrue(G[1]->next == nullptr);
		}
		TEST_METHOD(_GraphAbjList_destination_)
		{
			Graph G{ 3 };
			G.AddEdge(0, 1, 2);
			Assert::AreEqual(G[0]->destination, 1u);
			Assert::AreEqual(G[1]->destination, 0u);
			Assert::AreEqual(G[0]->weight, 2u);
			Assert::AreEqual(G[1]->weight, 2u);
		}
		TEST_METHOD(_Same_vectors_)
		{
			std::vector<int> v1{ 1, 2, 3 };
			std::vector<int> v2{ v1 };
			std::vector<int> v3{ 1, 2, 4 };
			std::vector<int> v4{ 1, 2 };
			Assert::IsTrue(SameRoutes(v1, v2));
			Assert::IsFalse(SameRoutes(v1, v3));
			Assert::IsFalse(SameRoutes(v1, v4));
		}
		TEST_METHOD(_DijkstraAlgorithm_1th_example_)
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
			std::vector<unsigned> path_1 = DijkstraAlgorithm(G, 1 - 1, 5 - 1, std::vector<unsigned>(), std::vector<unsigned>());
			std::vector<unsigned> path_1_correct{ 0, 2, 5, 4 };
			Assert::IsTrue(SameRoutes(path_1, path_1_correct));
		}
		TEST_METHOD(_DijkstraAlgorithm_2nd_example_)
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
			std::vector<unsigned> path_1 = DijkstraAlgorithm(G, 4 - 1, 1 - 1, std::vector<unsigned>(), std::vector<unsigned>());
			std::vector<unsigned> path_1_correct{ 3, 2, 0 };
			Assert::IsTrue(SameRoutes(path_1, path_1_correct));
		}
	};
}
