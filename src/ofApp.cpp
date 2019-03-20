#include "ofApp.h"

//Features:
//RESOLVED: Implement a resource manager
//RESOLVED: Implement a proper coordinate system + camera
//ToDo: Implement a proper render order system
//RESOLVED: Implement a better input system?
//ToDo: Proper gamestate system instead of this hacked together stuff
//ToDo: Add lifespan to enemies
//ToDo: Continuous collision detection for bullets
//ToDo: Add screenshake (part of the cam system)
//ToDo: Add components system to entities?
//ToDo: Implement a good collision system?
//ToDo: Implement a good component/parenting system?

//Optimizations:
//ToDo: Implement listener systems for more things rather than the mess currently
//ToDo: Implement object pool for bullets and particles
//RESOLVED?: Fix reliability problems
//ToDo: Multi-threading for particles?

//Testing:
//ToDo: Test Input class
//ToDo: Test EntitySystem render order system

//NOTE FOR GRADER: "EntitySystem" is just a genericized "SpriteSystem" for the most part.

//--------------------------------------------------------------
void ofApp::setup(){
	//cam.setupPerspective();
	input.setCamera(&cam);
	cam.setPosition(ofVec3f(0.0f, 0.0f, 1000));

	cam.enableOrtho();
}

//--------------------------------------------------------------
void ofApp::update(){
	//cam.setPosition(ofVec3f(ofRandomf(), ofRandomf(), 1000));
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	/*
	ofSetColor(ofColor::dimGrey);
	ofDrawGrid(32.0f, 18, true, false, false, true);
	*/

	ofSetColor(0, 255, 0);
	ofDrawCircle(glm::vec3(0.0f, 0.0f, 10.0f), 10);

	ofSetColor(255, 0, 0);
	ofDrawCircle(glm::vec3(0.0f, 0.0f, -10.0f), 8);

	ofSetColor(0, 0, 255);
	ofDrawCircle(input.getMouseWorldPos(), 8);

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	input.setKeyDown(key, true);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	input.setKeyDown(key, false);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	input.setMousePos(glm::vec3(x, y, 0.0f));
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	input.setMousePos(glm::vec3(x, y, 0.0f));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	input.setMouseDown(button, true);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	input.setMouseDown(button, false);
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
