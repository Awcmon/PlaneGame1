#include "ofApp.h"

//Features:
//RESOLVED: Implement a resource manager
//ToDo: Implement a proper coordinate system + camera
//ToDo: Implement a proper render order system
//RESOLVED: Implement a better input system?
//ToDo: Proper gamestate system instead of this hacked together stuff
//ToDo: Add lifespan to enemies
//ToDo: Continuous collision detection for bullets
//ToDo: Add screenshake (part of the cam system)
//ToDo: Add components system to entities?

//Optimizations:
//ToDo: Implement listener systems for more things rather than the mess currently
//ToDo: Implement object pool for bullets and particles
//RESOLVED?: Fix reliability problems
//ToDo: Multi-threading for particles?

//Testing:
//ToDo: Test Input class
//ToDo: Test Player class

//NOTE FOR GRADER: "EntitySystem" is just a genericized "SpriteSystem" for the most part.

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

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
