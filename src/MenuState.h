#pragma once

#include "GameState.h"
#include "MainStage.h"

class MenuState : public GameState
{
public:
	void setup();
	void update();
	void draw();
};
