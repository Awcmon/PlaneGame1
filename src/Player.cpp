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

		Particle* shootPuff = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
		shootPuff->setVel(ofVec2f(ofRandomf() * 10.0f, -30.0f + ofRandomf() * 15.0f));
		shootPuff->setAng(ofRandomf()*180.0f);
		shootPuff->setPos(toWorld(ofVec2f(32.0f, 0.0f)));
		shootPuff->setStartScale(0.4f);
		shootPuff->setEndScale(3.0f);
		shootPuff->setLifespan(100);
		shootPuff->setStartAlpha(255.0f);
		shootPuff->setEndAlpha(0.0f);
		ents->add(shootPuff, LAYER_FG_BOTTOM);

		ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * 2.0f);

		ents->add(bullet, LAYER_FG_BOTTOM);

		ents->rm->getSound("sounds\\shoot2.wav").play();
		lastShootTime = ofGetElapsedTimeMillis();
	}

	Particle* enginePuff1 = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
	enginePuff1->setVel(ofVec2f(ofRandomf() * 2.0f, -50.0f + ofRandomf() * 25.0f));
	enginePuff1->setAng(ofRandomf()*180.0f);
	enginePuff1->setPos(toWorld(ofVec2f(-32.0f, 6.0f)));
	enginePuff1->setStartScale(0.0f);
	enginePuff1->setEndScale(3.0f);
	enginePuff1->setLifespan(200);
	enginePuff1->setStartAlpha(255.0f);
	enginePuff1->setEndAlpha(0.0f);
	ents->add(enginePuff1, LAYER_FG_BOTTOM);

	Particle* enginePuff2 = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
	enginePuff2->setVel(ofVec2f(ofRandomf() * 2.0f, -50.0f + ofRandomf() * 25.0f));
	enginePuff2->setAng(ofRandomf()*180.0f);
	enginePuff2->setPos(toWorld(ofVec2f(-32.0f, -6.0f)));
	enginePuff2->setStartScale(0.0f);
	enginePuff2->setEndScale(3.0f);
	enginePuff2->setLifespan(200);
	enginePuff2->setStartAlpha(255.0f);
	enginePuff2->setEndAlpha(0.0f);
	ents->add(enginePuff2, LAYER_FG_BOTTOM);
}
