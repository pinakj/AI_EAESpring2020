#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include "Graph.h"
#include "Boid.h"
#include "Graph.h"
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

	struct Grid
	{
		//120
		int grid[16][9];

		Grid()
		{
			int index = 0;
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					grid[i][j] = index;
					index++;
				}
			}
		}

		ofVec2f getPos(int node)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (grid[i][j] == node)
					{
						return ofVec2f(j*120+60,i*120+60);
					}
				}
			}
		}

		int getNode(ofVec2f pos)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if ((pos.x > j * 120 && pos.x < j * 120 + 120) && (pos.y > i * 120 && pos.y < i * 120 + 120))
					{
						return grid[i][j];
					}
				}
			}
			return -1;

		}
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
					return;
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
	int nextIndex;
	SearchingAlgorithm() { nextIndex = 1; }
	static std::vector<int> pathfindDijkstra(Graph graph, int start, int end);
	static std::vector<int> pathfindAStar(Graph graph, int start, int end, Heuristic heuristic);
	std::vector<int> manhattanHeuristic(Grid grid, Graph graph, int goal);


	static void print(std::vector<int> path);

	Algorithm::SteeringOutput Pathfinding(Boid* character, vector<int> path, SearchingAlgorithm::Grid grid, float i_distanceFromNode, float i_maxLinear, float i_targetRadiusLinear, float i_targetRadiusAngular, float i_slowRadiusLinear, float i_slowRadiusAngular, float i_maxAngular, float i_maxRot);



};