#pragma once

#include "ofMain.h"
#include <array>

class Input
{
	glm::vec3 mPos;
	std::array<bool, 512> keysDown;
	std::array<bool, 3> mouseButtonsDown;
public:
	Input();

	glm::vec3 getMousePos();
	bool keyDown(int key);
	bool keyPressed(int key);
	bool keyReleased(int key);
	bool mouseDown(int button);

	void setMousePos(glm::vec3 _mPos);
	void setKeyDown(int key, bool down);
	void setMouseDown(int button, bool down);
};
