#pragma once

#include "Sprite.h"
#include "Particle.h"

class Enemy : public Sprite
{
public:
	Enemy();
	void update();
	void setTarget(Entity* _target);

	float targAng;
	float speed;

	Entity* target;
	bool flybySounded;
};
