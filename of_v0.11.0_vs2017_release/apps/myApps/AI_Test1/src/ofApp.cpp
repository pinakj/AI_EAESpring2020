#include "ofApp.h"
#include "Boid.h"
#include "Graph.h"
#include "SearchingAlgorithm.h"

int sim = 0;
Graph testGraph;
//--------------------------------------------------------------
void ofApp::setup(){
	isUpdating = false;
	width = 1920;
	height = 1080;

	vector<int> path;

	ofSetWindowShape(width, height);
	boid1 = new Boid(50, 50, 50, 100);

	testGraph = Graph::Graph("Graphs/test.csv");

	/***********************DIJKSTRAS AND A STAR ON TEST GRAPH ***************************************/

	vector<int> constantTestHeuristic;
	vector<int> randomTestHeuristic;

	SearchingAlgorithm::Heuristic testHeuristic1;
	SearchingAlgorithm::Heuristic testHeuristic2;


	for (int i = 0; i < testGraph.graph.size(); i++)
	{
		constantTestHeuristic.push_back(15);
		randomTestHeuristic.push_back(rand() % 30);
	}

	testHeuristic1 = constantTestHeuristic;
	testHeuristic2 = randomTestHeuristic;

	std::cout << "Running Dijkstra on test graph\n";
	path = SearchingAlgorithm::pathfindDijkstra(testGraph, 18, 11);
	SearchingAlgorithm::print(path);

	std::cout << "Running A Star with random heuristic on test graph\n";
	path = SearchingAlgorithm::pathfindAStar(testGraph, 18, 11,testHeuristic2);
	SearchingAlgorithm::print(path);

	std::cout << "Running A Star with constant heuristic on test graph\n";
	path = SearchingAlgorithm::pathfindAStar(testGraph, 18, 11, testHeuristic1);
	SearchingAlgorithm::print(path);
}


//--------------------------------------------------------------
void ofApp::update()
{

	if (sim == 0)
	{
		Algorithm::basicMotion(boid1);
	}

	boid1->update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw(){


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
	if (button == 0)
	{
		printf("Here");
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
