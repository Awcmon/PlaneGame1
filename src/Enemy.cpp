#include "Enemy.h"

Enemy::Enemy()
{
	setID("enemy");
	//lifeSpan = 10000;
	createTime = ofGetElapsedTimeMillis();
	lifespan = 4000;
	speed = 35.0f;
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
	vel = ofVec2f(speed, 0.0f).getRotated(ang);
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
	
}

void Enemy::setTarget(Entity * _target)
{
	target = _target;
}
