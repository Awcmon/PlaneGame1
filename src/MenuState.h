#pragma once

//Alan Duong, 03/31/19
//Gamestate for the main menu

#include "GameState.h"
#include "MainStage.h"

class MenuState : public GameState
{
public:
	void setup();
	void update();
	void draw();

	float titleTargY;
	float titleY;

	float clickTargX;
	float clickX;

	Sprite* title;
	Sprite* clicktobegin;
	Sprite* plane;

	bool transitionStarted;
	bool fadeStarted;
	uint64_t fadeStartTime;
};
