#include "Input.h"

Input::Input()
{
	mPos = glm::vec3(0.0f, 0.0f, 0.0f);
	for (size_t i = 0; i < keysDown.size(); ++i)
	{
		keysDown[i] = false;
	}
}

glm::vec3 Input::getMousePos()
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

void Input::setMousePos(glm::vec3 _mPos)
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
