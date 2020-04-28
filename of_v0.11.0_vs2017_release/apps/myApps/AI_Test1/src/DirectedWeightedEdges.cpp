#include "DirectedWeightedEdges.h"

DirectedWeightedEdges::DirectedWeightedEdges(int from, int to, float cost)
{
	fromNode = from;
	toNode = to;
	nodeCost = cost;
}

DirectedWeightedEdges::DirectedWeightedEdges()
{
	fromNode = 0;
	toNode = 0;
	nodeCost = 0;
}
