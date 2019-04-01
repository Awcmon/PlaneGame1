#pragma once

//Alan Duong, 03/31/19
//This is a bullet that the player shoots.
//It destroys enemies.

#include "Sprite.h"
#include "Particle.h"
#include "Player.h"
#include "Debris.h"

class Bullet : public Sprite
{
public:
	Bullet();
	Bullet(ofImage* _image);

	virtual void update();
};
