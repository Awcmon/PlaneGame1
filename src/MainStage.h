#pragma once

#include "GameState.h"
#include "Enemy.h"
#include "unordered_set"
#include "util.h"

class MainStage : public GameState
{
public:
	void setup();
	void update();
	void draw();

	Player* player;

	uint64_t nextEnemySpawnTime;

	std::vector<ofVec2f> warningPoints;
};
