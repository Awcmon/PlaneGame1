
#include "Bullet.h"

//Alan Duong, 03/31/19
//This is a bullet that the player shoots.
//It destroys enemies.

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
	//Find all enemies, and see if we are touching any.
	for (size_t i = 0; i < ents->entities[LAYER_FG_MID].size(); ++i)
	{
		Entity* curEnt = ents->entities[LAYER_FG_MID][i];
		if (curEnt->id == "enemy")
		{
			if (pos.squareDistance(curEnt->pos) < 1024.0f)
			{
				//Assume we are owned by a player and increase their score.
				((Player*)owner)->score += (int)curEnt->getVel().lengthSquared();
				((Player*)owner)->enemiesKilled++;

				//Play a close explosion sound if the enemy is close, distant if not.
				if (pos.lengthSquared() < 600.0f * 600.0f)
				{
					ents->rm->getSound("sounds\\explosion_generic_small_close_0" + std::to_string((rand() % 3) + 1) + ".wav")->play();
				}
				else
				{
					ents->rm->getSound("sounds\\explosion_generic_small_distant_0" + std::to_string((rand() % 3) + 1) + ".wav")->play();
				}

				//make it so the viewpunch is more intense the closer the explosion is to the player.
				ofVec2f diff = owner->getPos() - curEnt->getPos();
				//ents->view->posViewPunch(((diff.normalized() * 30000.0f) / (diff.length() + 0.1f)) + ofVec2f(ofRandomf(), ofRandomf()) * 0.65f);
				ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * (20000.0f) / (diff.length() + 0.1f));

				//explosion particle effects.
				Particle* lingeringPuff = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
				lingeringPuff->applyForce(ofVec2f(ofRandomf() * 5.0f, -15.0f + ofRandomf() * 5.0f));
				lingeringPuff->setAng(ofRandomf()*180.0f);
				lingeringPuff->setPos(pos);
				lingeringPuff->setStartScale(2.0f);
				lingeringPuff->setEndScale(5.0f);
				lingeringPuff->setLifespan(500);
				lingeringPuff->setColor(ofColor(1.0f, 1.0f, 1.0f) * 130.0f);
				lingeringPuff->setStartAlpha(155.0f);
				lingeringPuff->setEndAlpha(0.0f);
				ents->add(lingeringPuff, LAYER_FG_BOTTOM);

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
					smokePuff->setEndAlpha(100.0f);
					ents->add(smokePuff, LAYER_FG_BOTTOM);
				}
				Particle* bang = new Particle(ents->rm->getImage("images\\bang32_1.png"));
				bang->applyForce(ofVec2f(0.0f, -15.0f));
				bang->setAng(ofRandomf()*180.0f);
				bang->setPos(pos);
				bang->setStartScale(0.0f);
				bang->setEndScale(4.0f);
				bang->setLifespan(55);
				//bang->setColor(ofColor(1.0f, 0.0f, 0.0f) * 200.0f);
				bang->setColor(ofColor::orangeRed);
				bang->setStartAlpha(255.0f);
				bang->setEndAlpha(100.0f);
				ents->add(bang, LAYER_FG_BOTTOM);

				for (int i = 0; i < rand() % 4 + 2; ++i)
				{
					Debris* debris = new Debris();
					debris->setImage(ents->rm->getImage("images\\debris1.png"));
					debris->setPos(curEnt->getPos());
					debris->setVel(curEnt->getVel() + ofVec2f(ofRandomf(), ofRandomf())*30.0f);
					debris->setAng(ofRandomf()*180.0f);
					debris->setAngVel(ofRandomf()*20.0f);
					debris->setLifespan(500);
					debris->setAlpha(150.0f);
					debris->setScale(ofRandomf()*2.0f + 0.5f);

					ents->add(debris, LAYER_FG_BOTTOM);
				}
				
				//remove both the bullet and the enemy.
				curEnt->remove();
				remove();
				return;
			}
		}
	}
}
