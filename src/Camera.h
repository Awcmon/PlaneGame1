#pragma once

//Alan Duong, 03/31/19
//This is a wrapper for ofCamera to help do screenshake.

#include "ofMain.h"
#include "util.h"

class View
{
public:
	View();
	
	ofCamera cam;

	void posViewPunch(ofVec2f pos);
	void update();
	ofVec2f getTotalOffset();

	ofVec2f punchPos;

	ofVec2f offset; //used for screenshake and stuff
};
