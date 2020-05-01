#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include "Graph.h"
#include "DirectedWeightedEdges.h"
#include <math.h>

class SearchingAlgorithm
{
public:
	struct Heuristic {

		Heuristic(std::vector<int> temp)
		{
			heuristics = temp;
		}
		Heuristic() {};
		std::vector<int> heuristics;
	};

	struct NodeRecord
	{
		int node = -1;
		DirectedWeightedEdges connection = DirectedWeightedEdges();
		float costSoFar = 0.0f;
		float estimatedTotalCost = 0.0f;
	};

	struct PriorityQueue
	{
		std::vector <std::pair<NodeRecord, int>> elements;

		void put(NodeRecord node, int prio)
		{
			std::pair<NodeRecord, int> element;
			int eSize = elements.size();
			for (int i = 0; i < eSize; i++)
			{
				element = elements[i];
				if (element.second > prio)
				{
					elements.insert(elements.begin() + i, std::pair<NodeRecord, int>(node, prio));
				}
			}
			elements.push_back(std::pair<NodeRecord,int>(node,prio));
		}

		NodeRecord get()
		{
			NodeRecord ret = elements.front().first;
			elements.erase(elements.begin());
			return ret;
		}

		bool empty() const
		{
			return elements.empty();
		}

		bool contains(int node)
		{
			for (std::pair<NodeRecord, int> element : elements)
			{
				if (element.first.node == node)
				{
					return true;
				}
			}
			return false;
		}

		NodeRecord find(int node)
		{
			std::pair<NodeRecord, int> element;
			NodeRecord temp;
			int eSize = elements.size();

			for (int i = 0; i < eSize; i++)
			{
				element = elements[i];
				if (element.first.node == node)
				{
					temp = element.first;
					elements.erase(elements.begin() + i);
					return temp;
				}
			}
			return temp;
		}

	};
public:
	static std::vector<int> pathfindDijkstra(Graph graph, int start, int end);
	static std::vector<int> pathfindAStar(Graph graph, int start, int end, Heuristic heuristic);

	static void print(std::vector<int> path);
};