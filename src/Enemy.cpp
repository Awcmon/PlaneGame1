#include "Enemy.h"

Enemy::Enemy()
{
	setID("enemy");
	//lifeSpan = 10000;
	createTime = ofGetElapsedTimeMillis();
	lifespan = 4000;
	speed = 35.0f;
	target = nullptr;
}

void Enemy::update()
{
	Sprite::update();
	if (target == nullptr) { return; }
	targAng = ofVec2f(1.0f, 0.0f).angle((target->getPos() - pos));
	//ang = approachAngle(ang, targAng, angleDifference(targAng, ang)*0.02f);
	ang = approachAngle(ang, targAng, 0.1f);
	vel = ofVec2f(speed, 0.0f).getRotated(ang);
}

void Enemy::setTarget(Entity * _target)
{
	target = _target;
}
