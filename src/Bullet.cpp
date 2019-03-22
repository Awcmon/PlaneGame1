
#include "Bullet.h"

Bullet::Bullet()
{
	setID("bullet");
	lifespan = 2000;
	createTime = ofGetElapsedTimeMillis();
}

Bullet::Bullet(ofImage* _image)
{
	setID("bullet");
	setImage(_image);
	lifespan = 2000;
	createTime = ofGetElapsedTimeMillis();
}

//handle collisions here for now lmao
//ToDO: Make this a lot better oh god
void Bullet::update()
{
	Sprite::update();

	/*
	Particle* shootPuff = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
	shootPuff->setVel(ofVec2f(ofRandomf() * 1.0f, -20.0f + ofRandomf() * 1.0f));
	shootPuff->setAng(ofRandomf()*180.0f);
	shootPuff->setPos(toWorld(ofVec2f(0.0f, 0.0f)));
	shootPuff->setStartScale(0.1f);
	shootPuff->setEndScale(0.5f);
	shootPuff->setLifespan(30);
	shootPuff->setStartAlpha(255.0f);
	shootPuff->setEndAlpha(0.0f);
	ents->add(shootPuff, LAYER_FG_BOTTOM);
	*/

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
