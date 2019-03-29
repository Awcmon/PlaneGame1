#pragma once

#include "ofMain.h"
#include "Entity.h"
#include "Input.h"
#include "Sprite.h"
#include "Player.h"
#include "Camera.h"
#include "OceanWaves.h"

class GameState
{
public:
	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	void init(EntitySystem* _ents, ResourceManager* _rm, Input* _input, View* _view, GameState** _curGameState);

	void changeState(GameState * newGameState);

	EntitySystem* ents;
	ResourceManager* rm;
	Input* input;
	View* view;

	GameState** curGameState;
};

void changeGameState(GameState * newGameState, EntitySystem* ents, ResourceManager* rm, Input* input, View* view, GameState** curGameState);
