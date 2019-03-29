#pragma once

#include "GameState.h"
#include "Enemy.h"

class MainStage : public GameState
{
public:
	void setup();
	void update();
	void draw();

	uint64_t lastEnemySpawnTime;
};
