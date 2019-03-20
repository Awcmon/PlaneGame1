
#include "Bullet.h"

Bullet::Bullet()
{
	setID("bullet");
	lifeSpan = 2000;
	createTime = ofGetElapsedTimeMillis();
}

Bullet::Bullet(ofImage _image)
{
	setID("bullet");
	setImage(_image);
	lifeSpan = 2000;
	createTime = ofGetElapsedTimeMillis();
}

//handle collisions here for now lmao
//ToDO: Make this a lot better oh god
void Bullet::update()
{
	Sprite::update();
	//DANGEROUS. only okay because the return
	/*
	for (size_t i = 0; i < ents->entities.size(); ++i)
	{
		Entity* curEnt = entSys->entities[i];
		if (curEnt->id == "enemy")
		{
			if (pos.squareDistance(curEnt->pos) < 1024.0f)
			{
				entSys->rm->getSound("sounds\\shipexplode.wav").play();
				curEnt->remove();
				remove();
				return;
			}
		}
	}
	*/
}
