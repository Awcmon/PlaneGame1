#include "MenuState.h"

void MenuState::setup()
{

	Sprite* carrier = new Sprite(rm->getImage("images\\carrier.png"));
	carrier->setPos(ofVec2f(0.0f, -10.0f));
	ents->add(carrier, LAYER_BG_TOP);

	clicktobegin = new Sprite(rm->getImage("images\\clicktobegin.png"));
	ents->add(clicktobegin, LAYER_FG_TOP);

	title = new Sprite(rm->getImage("images\\title.png"));
	ents->add(title, LAYER_FG_TOP);

	ofDisableAntiAliasing();
	plane = new Sprite(rm->getImage("images\\f14.png"));
	ents->add(plane, LAYER_FG_MID);
	plane->setScale(1.5f);
	plane->setAng(93.0f);
	plane->setPos(ofVec2f(127.0f, -210.0f));

	for (int i = 0; i < 64; ++i)
	{
		OceanWaves* ow = new OceanWaves();
		ow->setPos(ofVec2f(ofRandomf()*650.0f, ofRandomf()*500.0f));
		ow->setVel(ofVec2f(3.0f, -3.0f));
		ents->add(ow, LAYER_BG_BOTTOM);
	}

	titleY = -500.0f;
	titleTargY = 250.0f;

	clickX = -1000.0f;
	clickTargX = 0.0f;

	transitionStarted = false;
	fadeStarted = false;
	fadeStartTime = 0;
}

void MenuState::update()
{
	title->setPos(ofVec2f(ofRandomf()*0.65f, titleY + ofRandomf()*0.65f));
	titleY = approach(titleY, titleTargY, (titleTargY - titleY) * 0.025f);

	if (abs(titleTargY - titleY) < 5.0f || transitionStarted)
	{
		clickX = approach(clickX, clickTargX, (clickTargX - clickX) * 0.025f);
	}
	clicktobegin->setPos(ofVec2f(clickX, -350.0f));

	clicktobegin->setAlpha(200.0f * (sinf(5.0f*ofGetElapsedTimef()) + 1.0f)*0.5f + 55.0f);

	if (input->keyPressed('r'))
	{
		titleY = -500.0f;
		titleTargY = 250.0f;

		clickX = -1000.0f;
		clickTargX = 0.0f;
	}

	if ((input->mousePressed(0) || input->keyPressed(' ')) && !transitionStarted)
	{
		//ents->update();
		transitionStarted = true;
		//changeState(new MainStage());
	}

	if (transitionStarted)
	{
		titleTargY = 800.0f;
		clickTargX = 2000.0f;

		plane->applyForce(plane->forward() * 0.2f);
		ents->view->posViewPunch(ofVec2f(ofRandomf(), ofRandomf()) * 5.0f);
		ents->rm->playSoundLoop("soundloops\\afterburner.wav");

		Particle* burner1 = new Particle(ents->rm->getImage("images\\bang32_1.png"));
		burner1->setVel(plane->getVel()*0.9f);
		burner1->setAng(ofRandomf()*180.0f);
		burner1->setAngVel(ofRandomf()*40.0f);
		burner1->setPos(plane->toWorld(ofVec2f(-36.0f, 6.0f)));
		burner1->setStartScale(0.8f);
		burner1->setEndScale(0.0f);
		burner1->setLifespan(55);
		burner1->setStartAlpha(255.0f);
		burner1->setEndAlpha(0.0f);
		burner1->setColor(ofColor::orange);
		ents->add(burner1, LAYER_FG_BOTTOM);

		Particle* burner2 = new Particle(ents->rm->getImage("images\\bang32_1.png"));
		burner2->setVel(plane->getVel()*0.9f);
		burner2->setAng(ofRandomf()*180.0f);
		burner2->setAngVel(ofRandomf()*40.0f);
		burner2->setPos(plane->toWorld(ofVec2f(-36.0f, -6.0f)));
		burner2->setStartScale(0.8f);
		burner2->setEndScale(0.0f);
		burner2->setLifespan(55);
		burner2->setStartAlpha(255.0f);
		burner2->setEndAlpha(0.0f);
		burner2->setColor(ofColor::orange);
		ents->add(burner2, LAYER_FG_BOTTOM);

		Particle* enginePuff1 = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
		enginePuff1->setVel(ofVec2f(ofRandomf() * 2.0f, -5.0f + ofRandomf() * 5.0f));
		enginePuff1->setAng(ofRandomf()*180.0f);
		enginePuff1->setPos(plane->toWorld(ofVec2f(-32.0f + ofRandomf()*150.0f, 6.0f)));
		enginePuff1->setStartScale(0.0f);
		enginePuff1->setEndScale(5.0f);
		enginePuff1->setLifespan(500);
		enginePuff1->setStartAlpha(200.0f);
		enginePuff1->setEndAlpha(0.0f);
		ents->add(enginePuff1, LAYER_FG_BOTTOM);

		Particle* enginePuff2 = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
		enginePuff2->setVel(ofVec2f(ofRandomf() * 2.0f, -5.0f + ofRandomf() * 5.0f));
		enginePuff2->setAng(ofRandomf()*180.0f);
		enginePuff2->setPos(plane->toWorld(ofVec2f(-32.0f + ofRandomf()*150.0f, -6.0f)));
		enginePuff2->setStartScale(0.0f);
		enginePuff2->setEndScale(5.0f);
		enginePuff2->setLifespan(500);
		enginePuff2->setStartAlpha(200.0f);
		enginePuff2->setEndAlpha(0.0f);
		ents->add(enginePuff2, LAYER_FG_BOTTOM);

		if (plane->getPos().y > 1500.0f && !fadeStarted)
		{
			Particle* white = new Particle(ents->rm->getImage("images\\white.png"));
			white->setPos(ofVec2f(0.0f, 0.0f));
			white->setStartScale(20.0f);
			white->setEndScale(20.0f);
			white->setLifespan(2200);
			white->setStartAlpha(0.0f);
			white->setEndAlpha(500.0f);
			white->setColor(ofColor::black);
			ents->add(white, LAYER_FG_TOP);

			fadeStarted = true;
			fadeStartTime = ofGetElapsedTimeMillis();
		}
	}

	if (fadeStarted)
	{
		if (ofGetElapsedTimeMillis() > fadeStartTime + 2000)
		{
			ofSetBackgroundColor(ofColor::black);
			ents->rm->stopSoundLoop("soundloops\\afterburner.wav");
			ents->clear();
			changeState(new MainStage());
		}
	}
}

void MenuState::draw()
{
	
}
