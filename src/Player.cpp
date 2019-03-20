#include "Player.h"

//ToDo: Make weapons their own entities that are attached to the plane?
Player::Player(ofImage _image, Input* _input)
{
	setImage(_image);
	input = _input;
	lastShootTime = 0;
	shootPeriod = 40;
	shootSpeed = 30.0f;
}

void Player::handleInput()
{
	targetPos = input->getMouseWorldPos();
}

void Player::update()
{
	handleInput();

	ofVec2f diff = targetPos - pos - ofVec2f(0, 32.0f);
	pos += diff * 0.2f;

	if (diff.y < 0) { diff.y *= -1.0f; } //reflect across x-axis
										 //ang = diff.angle(ofVec2f(1, 0));
	ang = ofVec2f(1.0f, 0.0f).angle((targetPos - pos));
	
	//ang = clamp(normalizeAngle(-ang + 90.0f), -60.0f, 60.0f);
	if (input->mouseDown(0) && ofGetElapsedTimeMillis() > lastShootTime + shootPeriod)
	{
		Bullet* bullet = new Bullet(ents->rm->getImage("images\\bullet.png"));
		bullet->setVel(ofVec2f(shootSpeed, 0.0f).rotate(ang));
		bullet->setAng(ang);
		bullet->setPos(toWorld(ofVec2f(32.0f, 0.0f)));

		Particle* p = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
		p->setVel(ofVec2f(ofRandomf() * 10.0f, -30.0f + ofRandomf() * 15.0f));
		p->setAng(ofRandomf()*180.0f);
		p->setPos(toWorld(ofVec2f(32.0f, 0.0f)));
		p->setStartScale(0.4f);
		p->setEndScale(3.0f);
		p->setLifespan(100);
		p->setStartAlpha(255.0f);
		p->setEndAlpha(0.0f);
		ents->add(p, LAYER_FG_BOTTOM);

		ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * 2.0f);

		ents->add(bullet, LAYER_FG_BOTTOM);

		ents->rm->getSound("sounds\\shoot2.wav").play();
		lastShootTime = ofGetElapsedTimeMillis();
	}
}
