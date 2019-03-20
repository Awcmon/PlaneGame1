#include "Input.h"

Input::Input()
{
	mPos = ofVec2f(0.0f, 0.0f);
	for (size_t i = 0; i < keysDown.size(); ++i)
	{
		keysDown[i] = false;
	}
}

void Input::setCamera(ofCamera * _cam)
{
	cam = _cam;
}

ofVec2f Input::getMouseScreenPos()
{
	return mPos;
}

ofVec2f Input::getMouseWorldPos()
{
	glm::vec3 worldPos = cam->screenToWorld(glm::vec3(mPos.x, mPos.y, 0.0f));
	return ofVec2f(worldPos.x, worldPos.y);
}

bool Input::keyDown(int key)
{
	return keysDown[key];
}

bool Input::keyPressed(int key)
{
	return false;
}

bool Input::keyReleased(int key)
{
	return false;
}

bool Input::mouseDown(int button)
{
	return mouseButtonsDown[button];
}

void Input::setMousePos(ofVec2f _mPos)
{
	mPos = _mPos;
}

void Input::setKeyDown(int key, bool down)
{
	keysDown[key] = down;
}

void Input::setMouseDown(int button, bool down)
{
	mouseButtonsDown[button] = down;
}
