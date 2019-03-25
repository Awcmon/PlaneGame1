#pragma once

#include "Sprite.h"

class Enemy : public Sprite
{
	Enemy();
	void update();
	void setTarget(Entity* _target);

	Entity* target;
};
