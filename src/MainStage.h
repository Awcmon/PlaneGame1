#pragma once

#include "GameState.h"
#include "Enemy.h"

class MainStage : public GameState
{
public:
	void setup();
	void update();
	void draw();

	Player* player;

	uint64_t nextEnemySpawnTime;
};
