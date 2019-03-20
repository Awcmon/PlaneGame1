#include "Player.h"

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

		ents->add(bullet, LAYER_FG_BOTTOM);

		ents->rm->getSound("sounds\\shoot2.wav").play();
		lastShootTime = ofGetElapsedTimeMillis();
	}
}
