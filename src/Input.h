#pragma once

#include "ofMain.h"
#include "Camera.h"
#include <array>

class Input
{
	ofVec2f mPos;
	std::array<bool, 512> keysDown;
	std::array<bool, 3> mouseButtonsDown;
	View* view;
public:
	Input();

	void setView(View* _cam);

	ofVec2f getMouseScreenPos();
	ofVec2f getMouseWorldPos();
	bool keyDown(int key);
	bool keyPressed(int key);
	bool keyReleased(int key);
	bool mouseDown(int button);

	void setMousePos(ofVec2f _mPos);
	void setKeyDown(int key, bool down);
	void setMouseDown(int button, bool down);
};
