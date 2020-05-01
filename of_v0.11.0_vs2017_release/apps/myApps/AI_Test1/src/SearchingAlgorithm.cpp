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
			open.put(endNodeRecord, endNodeRecord.costSoFar);
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
	int cnt = 0;
	cout << "\n";

	for (int node : path)
	{
		cout << node << " ";
		cnt++;

	}
	cout << "\n";

}

Algorithm::SteeringOutput  SearchingAlgorithm::Pathfinding(Boid * character, vector<int> path, SearchingAlgorithm::Grid grid, float i_distanceFromNode, float i_maxLinear, float i_targetRadiusLinear, float i_targetRadiusAngular, float i_slowRadiusLinear, float i_slowRadiusAngular, float i_maxAngular, float i_maxRot)
{
	Algorithm::SteeringOutput steering;
	Boid *target = new Boid(0,0,0,0);

	ofVec2f targetPos = grid.getPos(path[nextIndex]);

	ofVec2f distanceVector = targetPos - character->kinematic->pos;

	float distance = distanceVector.length();

	target->kinematic->pos = targetPos;

	steering.linear = Algorithm::DynamicArrive(character, target, i_maxLinear, i_targetRadiusLinear, i_slowRadiusLinear)->linear;
	steering.angular = Algorithm::lookWhereYouAreGoing(character, i_targetRadiusAngular, i_slowRadiusAngular, i_maxAngular, i_maxRot)->angular;

	if (nextIndex < path.size() - 1 && distance <= i_distanceFromNode)
	{
		nextIndex++;
	}

	return steering;
}

std::vector<int> SearchingAlgorithm::manhattanHeuristic(Grid grid, Graph graph, int goal)
{
	std::vector<int> temp;
	ofVec2f goalPos = grid.getPos(goal);

	int cnt = graph.graph.size();
	for (int i = 0; i < cnt; i++)
	{
		ofVec2f currPos = grid.getPos(i);

		ofVec2f distance = currPos - goalPos;

		int result = abs(currPos.x - goalPos.x) + abs(currPos.y - goalPos.y);

		temp.push_back(result);
	}

	return temp;
}


