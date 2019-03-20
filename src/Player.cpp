#include "Player.h"

Player::Player(ofImage _image, Input* _input)
{
	setImage(_image);
	input = _input;
	lastShootTime = 0;
	shootPeriod = 40;
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


		ents->rm->getSound("sounds\\shoot2.wav").play();
		lastShootTime = ofGetElapsedTimeMillis();
	}
}
