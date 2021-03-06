#include "ofApp.h"

//Alan Duong, 03/31/19
//Main app class.

//Engine Features:
//RESOLVED: Implement a resource manager
//RESOLVED: Implement a proper coordinate system + camera
//RESOLVED: Implement a proper render order system
//RESOLVED: Implement a better input system?
//RESOLVED: Proper gamestate system instead of this hacked together stuff
//TODO: Continuous collision detection for bullets
//RESOLVED: Add screenshake (part of the cam system)
//TODO: Add components system to entities?
//TODO: Implement a good collision system?
//TODO: Implement a good component/parenting system?
//TODO: Implement some sort of parallax system
//RESOLVED: Move lifespan functionality from Sprite to Entity?
//RESOLVED: Add physics
//RESOLVED: Implement AnimatedSprite

//Game Features:
//RESOLVED: Player engine sound
//RESOLVED: Player afterburner sound
//TODO: Ambient clouds
//RESOLVED (sort of): Scrolling background
//RESOLVED: Main menu
//RESOLVED: Implement roll sprites for player
//RESOLVED: Implement enemies and stuff
//RESOLVED: Implement a proper hud
//TODO: More realistic waves in menu
//RESOLVED: Menu transition to main stage
//RESOLVED: Add music
//RESOLVED: Better shoot sound (probably use a loop)
//RESOLVED: Implement explosions
//RESOLVED: Early warning HUD
//RESOLVED: Add lingering smoke, debris, to explosions
//RESOLVED: Explosion screenshake
//RESOLVED: Make explosions dependent on enemy velocity?
//TODO: Homing missile enemy
//RESOLVED: Add enemy flyby sound
//RESOLVED: Implement player gun overheating
//TODO: Make enemies shoot when close
//RESOLVED: Implement player getting killed
//RESOLVED: Ways to get back to main menu

//Optimizations:
//TODO: Implement listener systems for more things rather than the mess currently
//TODO: Implement object pool for bullets and particles
//RESOLVED?: Fix reliability problems
//TODO: Multi-threading for particles?
//RESOLVED: Make resource manager return pointers instead, to stop possibly expensive data duplication?
//TODO: Make a way to iterate only through entities in a specific layer(s)

//Testing:
//RESOLVED: Test Input class
//RESOLVED: Test EntitySystem render order system

//NOTE FOR GRADER: "EntitySystem" is just a genericized "SpriteSystem" for the most part.

//--------------------------------------------------------------
void ofApp::setup(){
	ofSeedRandom();

	ents.setResourceManager(&rm);
	ents.setView(&view);

	input.setView(&view);

	//cam.setupPerspective();
	view.cam.setPosition(ofVec3f(0.0f, 0.0f, 1000));
	view.cam.enableOrtho();

	changeGameState(new MenuState(), &ents, &rm, &input, &view, &curGameState);
}

//--------------------------------------------------------------
void ofApp::update(){
	//cam.setPosition(ofVec3f(ofRandomf(), ofRandomf(), 1000));
	if (curGameState == nullptr) { return; }
	/*
	if (input.keyPressed('f'))
	{
		ofToggleFullscreen();
	}
	*/
	view.update();
	ents.update();
	curGameState->update();
	input.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (curGameState == nullptr) { return; }
	//ofSetBackgroundColor(ofColor::cadetBlue);
	ofSetBackgroundColor(ofColor::navy);

	view.cam.begin();

	/*
	ofSetColor(ofColor::dimGrey);
	ofDrawGrid(32.0f, 24, true, false, false, true);
	*/

	/*
	ofSetColor(0, 255, 0);
	ofDrawCircle(glm::vec3(0.0f, 0.0f, 10.0f), 10);

	ofSetColor(255, 0, 0);
	ofDrawCircle(glm::vec3(0.0f, 0.0f, -10.0f), 8);

	ofSetColor(0, 0, 255);
	ofDrawCircle(input.getMouseWorldPos(), 8);
	*/

	ents.draw();

	/*
	ofSetColor(ofColor::dimGrey);
	ofDrawGrid(32.0f, 24, true, false, false, true);
	*/

	curGameState->draw();

	view.cam.end();

	/*
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Frame Rate: " + std::to_string(ofGetFrameRate()), ofGetWindowWidth() - 170, 15);
	ofDrawBitmapString("Entities: " + std::to_string(ents.size()), ofGetWindowWidth() - 170, 35);
	*/
}

void ofApp::exit()
{
	if (curGameState == nullptr) { return; }
	delete curGameState;
	curGameState = nullptr;
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
