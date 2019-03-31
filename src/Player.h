#pragma once

#include "Sprite.h"
#include "Input.h"
#include "util.h"
#include "Bullet.h"
#include "Particle.h"

class Player : public Sprite
{
	Input* input;

public:
	Player(ofImage* _image, Input* _input);
	void handleInput();
	void update();

	bool isDead();
	float getHeat();
	uint64_t getScore();
	void setScore(uint64_t _score);
	void setDead(bool _dead);

	ofVec2f targetPos;
	uint64_t lastShootTime;
	uint64_t shootPeriod;
	float shootSpeed;

	float heat;
	bool overheated;

	bool dead;

	uint64_t score;
};