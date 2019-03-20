#pragma once

#include "ofMain.h"
#include <array>

class Input
{
	ofVec2f mPos;
	std::array<bool, 512> keysDown;
	std::array<bool, 3> mouseButtonsDown;
public:
	Input();

	ofVec2f getMousePos();
	bool keyDown(int key);
	bool keyPressed(int key);
	bool keyReleased(int key);
	bool mouseDown(int button);

	void setMousePos(ofVec2f _mPos);
	void setKeyDown(int key, bool down);
	void setMouseDown(int button, bool down);
};
