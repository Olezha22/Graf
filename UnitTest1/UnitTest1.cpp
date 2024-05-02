#include "pch.h"
#include "CppUnitTest.h"
#include "../Graf/main.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(GraphTests)
	{
	public:

		TEST_METHOD(TestGetWeight)
		{
			Graph g(5);
			g.addEdge(0, 1, 2);
			g.addEdge(0, 2, 1);

			Assert::AreEqual(2, g.getWeight(0, 1));
		}

		TEST_METHOD(TestFindEdgesByWeight)
		{
			Graph g(5);
			g.addEdge(0, 1, 2);
			g.addEdge(0, 2, 1);
			g.addEdge(1, 2, 4);
			g.addEdge(2, 3, 2);
			g.addEdge(2, 4, 1);
			g.addEdge(3, 4, 5);

			vector<pair<int, int>> edgesWithWeight1 = g.findEdgesByWeight(1);
			Assert::AreEqual(size_t(2), edgesWithWeight1.size());
			Assert::AreEqual(0, edgesWithWeight1[0].first);
			Assert::AreEqual(2, edgesWithWeight1[0].second);
			Assert::AreEqual(2, edgesWithWeight1[1].first);
			Assert::AreEqual(4, edgesWithWeight1[1].second);
		}

		TEST_METHOD(TestAddEdge)
		{
			Graph g(5);
			g.addEdge(0, 1, 2);
			g.addEdge(0, 2, 1);
			g.addEdge(1, 2, 4);

			vector<pair<int, int>> edgesWithWeight1 = g.findEdgesByWeight(1);
			Assert::AreEqual(size_t(1), edgesWithWeight1.size());
		}

		TEST_METHOD(TestRemoveEdge)
		{
			Graph g(5);
			g.addEdge(0, 1, 2);
			g.addEdge(0, 2, 1);
			g.addEdge(1, 2, 4);
			g.removeEdge(0, 2);

			vector<pair<int, int>> edgesWithWeight1 = g.findEdgesByWeight(1);
			Assert::AreEqual(size_t(0), edgesWithWeight1.size());
		}
	};
}

