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

	};
public:
	static std::vector<int> pathfindDijkstra(Graph graph, int start, int end);
	static std::vector<int> pathfindAStar(Graph graph, int start, int end, Heuristic heuristic);

	static void print(std::vector<int> path);
};