#pragma once

//Alan Duong, 03/31/19
//Gamestate for the main stage of the game

#include "GameState.h"
#include "Enemy.h"
#include "unordered_set"
#include "util.h"
#include "SlowText.h"
#include <array>

struct WarningData
{
	ofVec2f pos;
	ofColor color;
	int alpha;
};

struct LineSegment
{
	ofVec2f p1;
	ofVec2f p2;
};

class MainStage : public GameState
{
public:
	void setup();
	void update();
	void draw();

	Player* player;

	uint64_t nextEnemySpawnTime;

	uint64_t gameStartTime;

	bool gameOver;
	uint64_t gameOverTime;

	std::vector<WarningData> warningPoints;
	std::array<LineSegment, 4> warningSegments;

	int phase;
	int unitPhase;
	uint64_t nextPhaseTime;

	int spawnPeriod;
};
