#pragma once

#include "Sprite.h"

class Enemy : public Sprite
{
public:
	Enemy();
	void update();
	void setTarget(Entity* _target);

	float targAng;
	float speed;

	Entity* target;
};
