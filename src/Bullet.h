#pragma once

#include "Sprite.h"

class Bullet : public Sprite
{
public:
	Bullet();
	Bullet(ofImage* _image);

	virtual void update();
};
