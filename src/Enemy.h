#pragma once

//Alan Duong, 03/31/19
//The enemies that kill and are killed by the player. In this game, they are the enemy planes.

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
