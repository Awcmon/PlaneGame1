#pragma once

//Alan Duong, 03/31/19
//Debris, typically emitted during explosions.
//They leave behind a smoke trail.

#include "Sprite.h"
#include "Particle.h"

class Debris : public Sprite
{
public:
	void update();
};
