#include "Enemy.h"
#include "Player.h"

//Alan Duong, 03/31/19
//The enemies that kill and are killed by the player. In this game, they are the enemy planes.

Enemy::Enemy()
{
	setID("enemy");
	//lifeSpan = 10000;
	createTime = ofGetElapsedTimeMillis();
	lifespan = 4000;
	speed = 25.0f;
	target = nullptr;
	flybySounded = false;
}

void Enemy::update()
{
	Sprite::update();
	if (target == nullptr) { return; }
	targAng = ofVec2f(1.0f, 0.0f).angle((target->getPos() - pos));
	//ang = approachAngle(ang, targAng, angleDifference(targAng, ang)*0.02f);
	ang = approachAngle(ang, targAng, 0.1f);
	vel = ofVec2f(speed, 0.0f).getRotated(ang) + ofVec2f(0.0f, -20.0f);
	if ((target->getPos() - pos).lengthSquared() < 600.0f * 600.0f && !flybySounded)
	{
		ents->rm->getSound("sounds\\missile_launch3.wav")->play();
		flybySounded = true;
	}

	for (int i = 0; i < 2; ++i)
	{
		Particle* enginePuff1 = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
		enginePuff1->setVel(-getVel()*1.5f + ofVec2f(1.0f, 1.0f) * ofRandomf() * 5.0f + -forward() * ofRandomf() * 15.0f);
		enginePuff1->setAng(ofRandomf()*180.0f);
		enginePuff1->setPos(toWorld(ofVec2f(-32.0f, 0.0f)));
		enginePuff1->setStartScale(0.0f);
		enginePuff1->setEndScale(3.0f);
		enginePuff1->setLifespan(75);
		enginePuff1->setStartAlpha(100.0f);
		enginePuff1->setEndAlpha(0.0f);
		ents->add(enginePuff1, LAYER_FG_BOTTOM);
	}
	
	if (target->getID() == "player")
	{
		Player* curEnt = (Player*)target;
		if (pos.squareDistance(curEnt->pos) < 1024.0f)
		{
			curEnt->setDead(true);

			if (pos.lengthSquared() < 600.0f * 600.0f)
			{
				ents->rm->getSound("sounds\\explosion_generic_small_close_0" + std::to_string((rand() % 3) + 1) + ".wav")->play();
			}
			else
			{
				ents->rm->getSound("sounds\\explosion_generic_small_distant_0" + std::to_string((rand() % 3) + 1) + ".wav")->play();
			}

			ofVec2f diff = getPos() - curEnt->getPos();

			//ents->view->posViewPunch(((diff.normalized() * 30000.0f) / (diff.length() + 0.1f)) + ofVec2f(ofRandomf(), ofRandomf()) * 0.65f);

			ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * (10000.0f) / (diff.length() + 0.1f));

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

			remove();
			return;
		}
	}
}

void Enemy::setTarget(Entity * _target)
{
	target = _target;
}
