#include "SearchingAlgorithm.h"

std::vector<int> SearchingAlgorithm::pathfindDijkstra(Graph graph, int start, int end)
{
	NodeRecord startRecord;
	NodeRecord current;

	vector<DirectedWeightedEdges> connections;

	startRecord.node = start;
	startRecord.costSoFar = 0;

	PriorityQueue open;
	open.put(startRecord, startRecord.costSoFar);
	PriorityQueue closed;

	while (!open.empty())
	{
		current = open.get();

		if (current.node == end)
		{
			break;
		}
		connections = graph.getConnections(current.node);

		for (DirectedWeightedEdges connection : connections)
		{
			int endNode = connection.toNode;
			int endNodeCost = current.costSoFar + connection.nodeCost;

			NodeRecord endNodeRecord;

			if (closed.contains(endNode))
			{
				continue;
			}
			else if (open.contains(endNode))
			{
				endNodeRecord = open.find(endNode);
				if (endNodeRecord.costSoFar <= endNodeCost)
				{
					//put it back since it was popped out of vector
					open.put(endNodeRecord, endNodeRecord.costSoFar);
					continue;
				}
			}
			else
			{
				//Nothing 
			}
			endNodeRecord.node = endNode;
			endNodeRecord.costSoFar = endNodeCost;
			endNodeRecord.connection = connection;

			if (!open.contains(endNode))
			{
				open.put(endNodeRecord, endNodeRecord.costSoFar);
			}
		}
		closed.put(current, current.costSoFar);
	}
	if (current.node != end)
	{
		return vector<int>();
	}
	else
	{
		vector<int> path;

		while (current.node != start)
		{
			if (path.empty())
			{
				path.push_back(current.node);
			}
			else
			{
				path.insert(path.begin(), current.node);
			}
			current = closed.find(current.connection.fromNode);
		}
		path.insert(path.begin(), start);

		return path;
	}
}

std::vector<int> SearchingAlgorithm::pathfindAStar(Graph graph, int start, int end, Heuristic heuristic)
{
	NodeRecord startRecord;
	NodeRecord current;

	vector<DirectedWeightedEdges> connections;

	startRecord.node = start;
	startRecord.costSoFar = 0;

	PriorityQueue open;
	open.put(startRecord, startRecord.costSoFar);
	PriorityQueue closed;

	while (!open.empty())
	{
		current = open.get();

		if (current.node == end)
		{
			break;
		}
		connections = graph.getConnections(current.node);

		for (DirectedWeightedEdges connection : connections)
		{
			int endNode = connection.toNode;
			int endNodeCost = current.costSoFar + connection.nodeCost + heuristic.heuristics[endNode];

			NodeRecord endNodeRecord;

			if (closed.contains(endNode))
			{
				continue;
			}
			else if (open.contains(endNode))
			{
				endNodeRecord = open.find(endNode);
				if (endNodeRecord.costSoFar <= endNodeCost)
				{
					//put it back since it was popped out of vector
					open.put(endNodeRecord, endNodeRecord.costSoFar);
					continue;
				}
			}
			else
			{
				//Nothing 
			}
			endNodeRecord.node = endNode;
			endNodeRecord.costSoFar = endNodeCost;
			endNodeRecord.connection = connection;
			
			if (!open.contains(endNode))
			{
				open.put(endNodeRecord, endNodeRecord.costSoFar);
			}
		}
		closed.put(current, current.costSoFar);
	}
	if (current.node != end)
	{
		return vector<int>();
	}
	else
	{
		vector<int> path;

		while (current.node != start)
		{
			if (path.empty())
			{
				path.push_back(current.node);
			}
			else
			{
				path.insert(path.begin(), current.node);
			}
			current = closed.find(current.connection.fromNode);
		}
		path.insert(path.begin(), start);

		return path;
	}
}

void SearchingAlgorithm::print(std::vector<int> path)
{
	// TO DO:Fix this
	for (int node : path)
	{
		std::cout << node << ",";
	}
}
