#include "Enemy.h"

Enemy::Enemy()
{
	setID("enemy");
	//lifeSpan = 10000;
	createTime = ofGetElapsedTimeMillis();
	lifespan = 3000;
	target = NULL;
}

void Enemy::update()
{
	Sprite::update();

}

void Enemy::setTarget(Entity * _target)
{
}
