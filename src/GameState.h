#pragma once

#include "Input.h"

class GameState
{
	virtual void handleEvents(Input input) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};
