#pragma once

#include "GameState.h"
#include "Enemy.h"
#include "unordered_set"
#include "util.h"
#include "SlowText.h"

struct WarningData
{
	ofVec2f pos;
	ofColor color;
	int alpha;
};

class MainStage : public GameState
{
public:
	void setup();
	void update();
	void draw();

	Player* player;

	uint64_t nextEnemySpawnTime;

	std::vector<WarningData> warningPoints;
};
