#include "Player.h"

//ToDo: Make weapons their own entities that are attached to the plane?
Player::Player(ofImage* _image, Input* _input)
{
	setImage(_image);
	input = _input;
	lastShootTime = 0;
	shootPeriod = 20;
	shootSpeed = 40.0f;

	//set up animations
	slice(1, 3);
	anims["idle"] = { 100000000, {0} };
	anims["right"] = { 100000000,{ 1 } };
	anims["left"] = { 100000000,{ 2 } };

	score = 0;
}

void Player::handleInput()
{
	targetPos = input->getMouseWorldPos();
}

void Player::update()
{
	handleInput();

	ents->rm->playSoundLoop("soundloops\\air_distant.wav");

	//ambient turbulence
	ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * 0.65f);

	ofVec2f diff = targetPos - pos - ofVec2f(0, 32.0f);
	pos += diff * 0.2f;

	//calculate angle from plane to mouse pos
	float targAng = ofVec2f(1.0f, 0.0f).angle((targetPos - pos));

	//reflect angle if it is negative (when the plane is backing up/"slowing down")
	if (targAng < 0.0f)
	{
		targAng *= -1.0f;
	}
	
	//Deadzone near center of the craft to prevent spazzing when mouse is very close to actual pos of plane
	if (targetPos.y < pos.y + 32.0f && abs(targetPos.x - pos.x) < 1.0f)
	{
		targAng = 90.0f;
	}

	//clamp the target angle
	targAng = clamp(normalizeAngle(targAng), 60.0f, 120.0f);

	//approach target angle (smoothed)
	ang = approachAngle(ang, targAng, angleDifference(targAng, ang)*0.3f);
	ang = normalizeAngle(ang);

	if (ang < 70.0f)
	{
		setAnim("right");
	}
	else if (ang > 110.0f)
	{
		setAnim("left");
	}
	else
	{
		setAnim("idle");
	}
	
	if (input->mouseDown(0) && ofGetElapsedTimeMillis() > lastShootTime + shootPeriod)
	{
		Bullet* bullet = new Bullet(ents->rm->getImage("images\\bullet2.png"));
		bullet->setVel(ofVec2f(shootSpeed, 0.0f).rotate(ang));
		bullet->setAng(ang);
		bullet->setPos(toWorld(ofVec2f(32.0f, 0.0f)));
		bullet->setOwner(this);

		Particle* shootPuff = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
		shootPuff->setVel(ofVec2f(ofRandomf() * 10.0f, -30.0f + ofRandomf() * 15.0f));
		shootPuff->setAng(ofRandomf()*180.0f);
		shootPuff->setPos(toWorld(ofVec2f(32.0f, 0.0f)));
		shootPuff->setStartScale(0.4f);
		shootPuff->setEndScale(3.0f);
		shootPuff->setLifespan(100);
		shootPuff->setStartAlpha(255.0f);
		shootPuff->setEndAlpha(0.0f);
		shootPuff->setAngVel(30.0f);
		ents->add(shootPuff, LAYER_FG_BOTTOM);

		ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * 5.0f);

		ents->add(bullet, LAYER_FG_BOTTOM);

		//ents->rm->getSound("sounds\\rac_fire1.wav")->play();
		ents->rm->playSoundLoop("soundloops\\shootloop_100sp.wav");
		lastShootTime = ofGetElapsedTimeMillis();
	}
	
	if (!input->mouseDown(0))
	{
		ents->rm->stopSoundLoop("soundloops\\shootloop_100sp.wav");
	}

	if (targetPos.y > pos.y + 42.0f)
	{
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");

		ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * 3.0f);

		Particle* burner1 = new Particle(ents->rm->getImage("images\\bang32_1.png"));
		burner1->setVel(getVel()*0.9f);
		burner1->setAng(ofRandomf()*180.0f);
		burner1->setAngVel(ofRandomf()*40.0f);
		burner1->setPos(toWorld(ofVec2f(-24.0f, 6.0f)));
		burner1->setStartScale(0.6f);
		burner1->setEndScale(0.0f);
		burner1->setLifespan(55);
		burner1->setStartAlpha(255.0f);
		burner1->setEndAlpha(0.0f);
		burner1->setColor(ofColor::orange);
		ents->add(burner1, LAYER_FG_BOTTOM);

		Particle* burner2 = new Particle(ents->rm->getImage("images\\bang32_1.png"));
		burner2->setVel(getVel()*0.9f);
		burner2->setAng(ofRandomf()*180.0f);
		burner2->setAngVel(ofRandomf()*40.0f);
		burner2->setPos(toWorld(ofVec2f(-24.0f, -6.0f)));
		burner2->setStartScale(0.6f);
		burner2->setEndScale(0.0f);
		burner2->setLifespan(55);
		burner2->setStartAlpha(255.0f);
		burner2->setEndAlpha(0.0f);
		burner2->setColor(ofColor::orange);
		ents->add(burner2, LAYER_FG_BOTTOM);

		Particle* enginePuff1 = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
		enginePuff1->setVel(ofVec2f(ofRandomf() * 2.0f, -75.0f + ofRandomf() * 25.0f));
		enginePuff1->setAng(ofRandomf()*180.0f);
		enginePuff1->setPos(toWorld(ofVec2f(-32.0f, 6.0f)));
		enginePuff1->setStartScale(0.0f);
		enginePuff1->setEndScale(3.0f);
		enginePuff1->setLifespan(75);
		enginePuff1->setStartAlpha(100.0f);
		enginePuff1->setEndAlpha(0.0f);
		ents->add(enginePuff1, LAYER_FG_BOTTOM);

		Particle* enginePuff2 = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
		enginePuff2->setVel(ofVec2f(ofRandomf() * 2.0f, -75.0f + ofRandomf() * 25.0f));
		enginePuff2->setAng(ofRandomf()*180.0f);
		enginePuff2->setPos(toWorld(ofVec2f(-32.0f, -6.0f)));
		enginePuff2->setStartScale(0.0f);
		enginePuff2->setEndScale(3.0f);
		enginePuff2->setLifespan(75);
		enginePuff2->setStartAlpha(100.0f);
		enginePuff2->setEndAlpha(0.0f);
		ents->add(enginePuff2, LAYER_FG_BOTTOM);
	}
	else
	{
		ents->rm->stopSoundLoop("soundloops\\afterburner.wav");
	}

}
