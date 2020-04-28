#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include <math.h>

class DirectedWeightedEdges
{

public:
	DirectedWeightedEdges(int from, int to, float cost);
	DirectedWeightedEdges();
private:
	int fromNode;
	int toNode;
	int nodeCost;
};