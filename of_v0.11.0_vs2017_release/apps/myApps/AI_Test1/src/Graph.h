#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include "DirectedWeightedEdges.h"
#include <math.h>
#include <fstream>
#include <iostream>
using namespace std;

class Graph
{

public:

	void open(string name);
	vector<DirectedWeightedEdges> getConnections(int node);

	Graph(string name);
	Graph() {}

	std::vector<std::vector<DirectedWeightedEdges>> graph;


};

inline void Graph::open(string name)
{
	ifstream stream(name);

	int source, sink = 0;
	float cost = 0.0f;

	string x, y, z;

	while (getline(stream, x, ','))
	{
		getline(stream, y, ',');
		getline(stream, z, '\n');

		source = stoi(x);
		sink = stoi(y);
		cost = stof(z);

		//first edge in the graph
		if (source == graph.size())
		{
			vector<DirectedWeightedEdges> temp;
			temp.push_back(DirectedWeightedEdges(source, sink, cost));
			graph.push_back(temp);
		}

		//addition edge
		else
		{
			graph[source].push_back(DirectedWeightedEdges(source, sink, cost));
		}
	}
	stream.close();

}

inline Graph::Graph(string name)
{
	open(name);
}

inline vector<DirectedWeightedEdges> Graph::getConnections(int node)
{
	return graph[node];
}