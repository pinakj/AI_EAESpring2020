#include "ofApp.h"
#include "Boid.h"

int sim = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	isUpdating = false;
	width = 1920;
	height = 1080;

	ofSetWindowShape(width, height);
	boid1 = new Boid(50, 50, 50, 100);

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
