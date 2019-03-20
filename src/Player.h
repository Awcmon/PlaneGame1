#pragma once

#include "Sprite.h"
#include "Input.h"
#include "util.h"
#include "Bullet.h"

class Player : public Sprite
{
	Input* input;

public:
	Player(ofImage _image, Input* _input);
	void handleInput();
	void update();

	ofVec2f targetPos;
	uint64_t lastShootTime;
	uint64_t shootPeriod;
	float shootSpeed;
};