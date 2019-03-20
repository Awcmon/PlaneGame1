#include "Input.h"

Input::Input()
{
	mPos = ofVec2f(0.0f, 0.0f);
	for (size_t i = 0; i < keysDown.size(); ++i)
	{
		keysDown[i] = false;
	}
}

ofVec2f Input::getMousePos()
{
	return mPos;
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
