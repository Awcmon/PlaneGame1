#include "Player.h"

//Alan Duong, 03/31/19
//The player.

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
	enemiesKilled = 0;

	heat = 0.0f;
	overheated = false;
	dead = false;

	setID("player");
}

void Player::handleInput()
{
	targetPos = input->getMouseWorldPos();
}

void Player::update()
{
	//make the player basically disappear if they're dead.
	if (dead) 
	{ 
		setAlpha(0); 
		setPos(ofVec2f(100000.0f, 100000.0f));
		ents->rm->stopSoundLoop("soundloops\\shootloop_100sp.wav");
		ents->rm->stopSoundLoop("soundloops\\caution2.wav");
		ents->rm->stopSoundLoop("soundloops\\damagealarm.wav");
		ents->rm->stopSoundLoop("soundloops\\afterburner.wav");
		ents->rm->stopSoundLoop("soundloops\\air_distant.wav");
		return; 
	}

	handleInput();

	ents->rm->playSoundLoop("soundloops\\air_distant.wav");

	//ambient turbulence
	ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * 0.65f);

	//attempt to move the plane to the cursor
	ofVec2f diff = targetPos - pos - ofVec2f(0, 32.0f);
	pos += diff * 0.2f;

	//calculate angle from plane to mouse pos
	float targAng = ofVec2f(1.0f, 0.0f).angle((targetPos - pos));

	//reflect angle if it is negative (when the plane is backing up/"slowing down", aka moving to the bottom of the screen.)
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

	//set diff anims/sprites/frames
	//basically, make the plane look like it is rolling when it is turning.
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

	//dissipate the heat from the gun
	heat = approach(heat, 0.0f, heat*0.015f);
	
	//fire the gun
	if (input->mouseDown(0) && ofGetElapsedTimeMillis() > lastShootTime + shootPeriod && heat < 100.0f && !overheated)
	{
		//spawn the bullet
		Bullet* bullet = new Bullet(ents->rm->getImage("images\\bullet2.png"));
		bullet->setVel(ofVec2f(shootSpeed, 0.0f).rotate(ang));
		bullet->setAng(ang);
		bullet->setPos(toWorld(ofVec2f(32.0f, 0.0f)));
		bullet->setOwner(this);

		//muzzle smoke
		Particle* shootPuff = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
		shootPuff->setVel(ofVec2f(ofRandomf() * 5.0f, -20.0f + ofRandomf() * 10.0f));
		shootPuff->setAng(ofRandomf()*180.0f);
		shootPuff->setPos(toWorld(ofVec2f(32.0f, 0.0f)));
		shootPuff->setStartScale(0.4f);
		shootPuff->setEndScale(3.0f);
		shootPuff->setLifespan(100);
		shootPuff->setStartAlpha(200.0f);
		shootPuff->setEndAlpha(0.0f);
		shootPuff->setAngVel(30.0f);
		ents->add(shootPuff, LAYER_FG_BOTTOM);

		//viewpunch to make it look powerful
		ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * 8.0f);

		//actually add the bullet to the entity system now (this makes it appear on top of the smoke)
		ents->add(bullet, LAYER_FG_BOTTOM);

		//play the firing sound
		//ents->rm->getSound("sounds\\rac_fire1.wav")->play();
		ents->rm->playSoundLoop("soundloops\\shootloop_100sp.wav");

		//increase the gun heat
		heat += 3.3f;

		lastShootTime = ofGetElapsedTimeMillis();
	}
	
	//if the heat is too high, play a warning
	if (heat > 80.0f)
	{
		ents->rm->playSoundLoop("soundloops\\caution2.wav");
	}
	else
	{
		ents->rm->stopSoundLoop("soundloops\\caution2.wav");
	}

	//if the heat has hit the thresholdl, it has overheated
	if (heat >= 100.0f)
	{
		overheated = true;
		ents->rm->playSoundLoop("soundloops\\damagealarm.wav");
	}

	//overheating effects and end overheating when heat is low enough
	if (overheated)
	{
		Particle* overheatPuff = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
		overheatPuff->setVel(ofVec2f(ofRandomf() * 5.0f, -20.0f + ofRandomf() * 5.0f));
		overheatPuff->setAng(ofRandomf()*180.0f);
		overheatPuff->setPos(toWorld(ofVec2f(32.0f, 0.0f)));
		overheatPuff->setStartScale(0.4f);
		overheatPuff->setEndScale(3.0f);
		overheatPuff->setLifespan(200);
		overheatPuff->setStartAlpha(150.0f);
		overheatPuff->setEndAlpha(0.0f);
		overheatPuff->setAngVel(30.0f);
		ents->add(overheatPuff, LAYER_FG_BOTTOM);

		if (heat <= 5.0f)
		{
			ents->rm->stopSoundLoop("soundloops\\damagealarm.wav");
			overheated = false;
		}
	}
	
	//stop the shoot sound loop if we are not firing or cannot fire.
	if (!input->mouseDown(0) || overheated)
	{
		ents->rm->stopSoundLoop("soundloops\\shootloop_100sp.wav");
	}

	//if we are moving forwards fast enough, activate afterburner effects
	if (targetPos.y > pos.y + 42.0f)
	{
		//afterburner sound
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");

		//afterburner viewpunch so it looks powerful
		ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * 5.0f);

		//the flames on the engines
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

		//engine smoke
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

bool Player::isDead()
{
	return dead;
}

float Player::getHeat()
{
	return heat;
}

uint64_t Player::getScore()
{
	return score;
}

void Player::setScore(uint64_t _score)
{
	score = _score;
}

void Player::setDead(bool _dead)
{
	dead = _dead;
}

uint64_t Player::getEnemiesKilled()
{
	return enemiesKilled;
}
