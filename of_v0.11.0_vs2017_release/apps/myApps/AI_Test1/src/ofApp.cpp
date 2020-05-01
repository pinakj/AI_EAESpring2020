#include "ofApp.h"
#include "Boid.h"
#include "Graph.h"
#include "SearchingAlgorithm.h"

int sim = 0;
Graph testGraph;
Graph romeGraph;
Graph gridGraph;
SearchingAlgorithm::Grid grid;
vector<int> path;
SearchingAlgorithm *algorithm;

//--------------------------------------------------------------
void ofApp::setup(){
	isUpdating = false;
	width = 1920;
	height = 1080;


	ofSetWindowShape(width, height);
	boid1 = new Boid(50, 50, 30, 100);

	testGraph = Graph::Graph("Graphs/test.csv");
	romeGraph = Graph::Graph("Graphs/rome.csv");
	gridGraph = Graph::Graph("Graphs/grid.csv");


	algorithm = new SearchingAlgorithm();

	/***********************DIJKSTRAS AND A STAR ON TEST GRAPH ***************************************/

	vector<int> constantTestHeuristic;
	vector<int> randomTestHeuristic;

	SearchingAlgorithm::Heuristic testHeuristic1;
	SearchingAlgorithm::Heuristic testHeuristic2;


	for (int i = 0; i < testGraph.graph.size(); i++)
	{
		constantTestHeuristic.push_back(15);
		randomTestHeuristic.push_back(rand() % 60);
	}

	testHeuristic1 = constantTestHeuristic;
	testHeuristic2 = randomTestHeuristic;

	std::cout << "\nRunning Dijkstra on test graph\n";
	path = SearchingAlgorithm::pathfindDijkstra(testGraph, 4, 17);
	SearchingAlgorithm::print(path);

	std::cout << "\nRunning A Star with random heuristic on test graph\n";
	path = SearchingAlgorithm::pathfindAStar(testGraph, 4, 17,testHeuristic2);
	SearchingAlgorithm::print(path);

	std::cout << "\nRunning A Star with constant heuristic on test graph\n";
	path = SearchingAlgorithm::pathfindAStar(testGraph, 4, 17, testHeuristic1);
	SearchingAlgorithm::print(path);

	/***************************************************************************************/



	/***********************DIJKSTRAS AND A STAR ON ROME GRAPH ***************************************/

	vector<int> constantRomeHeuristic;
	vector<int> randomRomeHeuristic;

	SearchingAlgorithm::Heuristic romeHeuristic1;
	SearchingAlgorithm::Heuristic romeHeuristic2;


	for (int i = 0; i < romeGraph.graph.size(); i++)
	{
		constantRomeHeuristic.push_back(2500);
		randomRomeHeuristic.push_back(rand() % 1000);
	}

	romeHeuristic1 = constantRomeHeuristic;
	romeHeuristic2 = randomRomeHeuristic;

	std::cout << "\nRunning Dijkstra on test graph";
	path = SearchingAlgorithm::pathfindDijkstra(romeGraph, 245, 3129);
	SearchingAlgorithm::print(path);

	std::cout << "\nRunning A Star with random heuristic on test graph";
	path = SearchingAlgorithm::pathfindAStar(romeGraph, 245, 3129, romeHeuristic2);
	SearchingAlgorithm::print(path);

	std::cout << "\nRunning A Star with constant heuristic on test graph";
	path = SearchingAlgorithm::pathfindAStar(romeGraph, 245, 3129, romeHeuristic1);
	SearchingAlgorithm::print(path);

	/***************************************************************************************/

	grid = SearchingAlgorithm::Grid();
}

//--------------------------------------------------------------
void ofApp::update()
{

	if (sim == 0)
	{
		//Algorithm::basicMotion(boid1);
	}

	if (!path.empty())
	{
		Algorithm::SteeringOutput result = algorithm->Pathfinding(boid1,path,grid, 7.0f, 13.0f, 7.0f, 0.057f, 150.0f, 2.75f, .75f, PI);
		boid1->kinematic->angular = result.angular;
		boid1->kinematic->linear = result.linear;
	}

	boid1->update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0, 0, 0);
	for (int i = 1; i < 16; i++)
	{
		ofDrawLine(0 + i * 120, 0, 0 + i * 120, ofGetWindowHeight());
	}

	for (int i = 1; i < 9; i++)
	{
		ofDrawLine(0, 0 + i * 120, ofGetWindowWidth(), 0 + i * 120);
	}

	float obstacleRadius = 15;

	ofSetColor(0, 0, 0);
	ofDrawCircle(5 * 120 + 60, 3 * 120 + 60, obstacleRadius);
	ofDrawCircle(8 * 120 + 60, 8 * 120 + 60, obstacleRadius);
	ofDrawCircle(8 * 120 + 60, 7 * 120 + 60, obstacleRadius);
	ofDrawCircle(12 * 120 + 60, 3 * 120 + 60, obstacleRadius);
	ofDrawCircle(15 * 120 + 60, 11 * 120 + 60, obstacleRadius);
	ofDrawCircle(1 * 120 + 60, 0 * 120 + 60, obstacleRadius);
	ofDrawCircle(12 * 120 + 60, 0 * 120 + 60, obstacleRadius);
	ofDrawCircle(1 * 120 + 60, 1 * 120 + 60, obstacleRadius);
	ofDrawCircle(2 * 120 + 60, 1 * 120 + 60, obstacleRadius);
	ofDrawCircle(1 * 120 + 60, 2 * 120 + 60, obstacleRadius);
	ofDrawCircle(5 * 120 + 60, 1 * 120 + 60, obstacleRadius);
	ofDrawCircle(6 * 120 + 60, 1 * 120 + 60, obstacleRadius);
	ofDrawCircle(9 * 120 + 60, 3 * 120 + 60, obstacleRadius);
	ofDrawCircle(2 * 120 + 60, 4 * 120 + 60, obstacleRadius);
	ofDrawCircle(9 * 120 + 60, 4 * 120 + 60, obstacleRadius);
	ofDrawCircle(1 * 120 + 60, 5 * 120 + 60, obstacleRadius);
	ofDrawCircle(2 * 120 + 60, 5 * 120 + 60, obstacleRadius);
	ofDrawCircle(4 * 120 + 60, 5 * 120 + 60, obstacleRadius);
	ofDrawCircle(6 * 120 + 60, 5 * 120 + 60, obstacleRadius);
	ofDrawCircle(10 * 120 + 60, 6 * 120 + 60, obstacleRadius);
	ofDrawCircle(12 * 120 + 60, 6 * 120 + 60, obstacleRadius);
	ofDrawCircle(13 * 120 + 60, 6 * 120 + 60, obstacleRadius);
	ofDrawCircle(0 * 120 + 60, 7 * 120 + 60, obstacleRadius);
	ofDrawCircle(2 * 120 + 60, 7 * 120 + 60, obstacleRadius);
	ofDrawCircle(4 * 120 + 60, 7 * 120 + 60, obstacleRadius);
	ofDrawCircle(12 * 120 + 60, 7 * 120 + 60, obstacleRadius);
	ofDrawCircle(13 * 120 + 60, 7 * 120 + 60, obstacleRadius);
	ofDrawCircle(2 * 120 + 60, 8 * 120 + 60, obstacleRadius);
	ofDrawCircle(4 * 120 + 60, 8 * 120 + 60, obstacleRadius);
	ofDrawCircle(2 * 120 + 60, 9 * 120 + 60, obstacleRadius);
	ofDrawCircle(3 * 120 + 60, 9 * 120 + 60, obstacleRadius);
	ofDrawCircle(4 * 120 + 60, 9 * 120 + 60, obstacleRadius);
	ofDrawCircle(6 * 120 + 60, 9 * 120 + 60, obstacleRadius);
	ofDrawCircle(10 * 120 + 60, 9 * 120 + 60, obstacleRadius);
	ofDrawCircle(12 * 120 + 60, 9 * 120 + 60, obstacleRadius);
	ofDrawCircle(6 * 120 + 60, 10 * 120 + 60, obstacleRadius);
	ofDrawCircle(7 * 120 + 60, 10 * 120 + 60, obstacleRadius);
	ofDrawCircle(9 * 120 + 60, 10 * 120 + 60, obstacleRadius);
	ofDrawCircle(10 * 120 + 60, 10 * 120 + 60, obstacleRadius);
	ofDrawCircle(0 * 120 + 60, 11 * 120 + 60, obstacleRadius);
	boid1->makeBoid(boid1->kinematic->curDirection);

	for (Boid::breadCrumb crumb : boid1->breadCrumbs)
	{
		ofSetColor(0, 0, 0);
		ofVec3f temp = ofVec3f(0, 0, 0);
		temp.set(crumb.bCumbPos.x, crumb.bCumbPos.y);
		ofDrawBox(temp, 4);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	isUpdating = true;
	if (key == OF_KEY_RETURN)
	{
		sim++;
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	Boid* target = new Boid(0,0,0,0);
	if (button == 0)
	{
		path.clear();
		algorithm->nextIndex = 1;
		boid1->kinematic->vel = (ofVec2f(0.0f, 0.0f));
		boid1->kinematic->rot = (0.0f);
		boid1->kinematic->linear = (ofVec2f(0.0f, 0.0f));
		boid1->kinematic->angular = (0.0f);
		target->kinematic->pos = (ofVec2f(x, y));
		boid1->breadCrumbs.clear();

		std::cout << "Running A* on grid graph with manhattan distance\n";
		int goal = grid.getNode(target->kinematic->pos);
		int current = grid.getNode(boid1->kinematic->pos);

		SearchingAlgorithm::Heuristic manhattanHeuristic;

		if (!gridGraph.getConnections(goal).empty() && goal != current)
		{
			manhattanHeuristic = algorithm->manhattanHeuristic(grid, gridGraph, goal);
			path = SearchingAlgorithm::pathfindAStar(gridGraph, grid.getNode(boid1->kinematic->pos), goal, manhattanHeuristic);
			SearchingAlgorithm::print(path);
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

