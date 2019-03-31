
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
	for (size_t i = 0; i < ents->entities[LAYER_FG_MID].size(); ++i)
	{
		Entity* curEnt = ents->entities[LAYER_FG_MID][i];
		if (curEnt->id == "enemy")
		{
			if (pos.squareDistance(curEnt->pos) < 1024.0f)
			{
				((Player*)owner)->score += 100;

				if (pos.lengthSquared() < 600.0f * 600.0f)
				{
					ents->rm->getSound("sounds\\explosion_generic_small_close_0" + std::to_string((rand() % 3) + 1) + ".wav")->play();
				}
				else
				{
					ents->rm->getSound("sounds\\explosion_generic_small_distant_0" + std::to_string((rand() % 3) + 1) + ".wav")->play();
				}

				for (int i = 0; i < 10; ++i)
				{
					Particle* smokePuff = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
					smokePuff->applyForce(ofVec2f(ofRandomf() * 55.0f, -15.0f + ofRandomf() * 55.0f));
					smokePuff->setAng(ofRandomf()*180.0f);
					smokePuff->setPos(pos);
					smokePuff->setStartScale(0.0f);
					smokePuff->setEndScale(3.0f);
					smokePuff->setLifespan(55);
					smokePuff->setColor(ofColor(1.0f, 1.0f, 1.0f) * 130.0f);
					smokePuff->setStartAlpha(255.0f);
					smokePuff->setEndAlpha(0.0f);
					ents->add(smokePuff, LAYER_FG_BOTTOM);
				}
				Particle* bang = new Particle(ents->rm->getImage("images\\bang32_1.png"));
				bang->applyForce(ofVec2f(0.0f, -15.0f));
				bang->setAng(ofRandomf()*180.0f);
				bang->setPos(pos);
				bang->setStartScale(0.0f);
				bang->setEndScale(4.0f);
				bang->setLifespan(55);
				bang->setColor(ofColor(1.0f, 0.0f, 0.0f) * 200.0f);
				bang->setStartAlpha(255.0f);
				bang->setEndAlpha(0.0f);
				ents->add(bang, LAYER_FG_BOTTOM);
				

				curEnt->remove();
				remove();
				return;
			}
		}
	}
}
