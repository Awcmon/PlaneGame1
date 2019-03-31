#include "MenuState.h"

void MenuState::setup()
{

	Sprite* carrier = new Sprite(rm->getImage("images\\carrier.png"));
	ents->add(carrier, LAYER_BG_TOP);

	clicktobegin = new Sprite(rm->getImage("images\\clicktobegin.png"));
	ents->add(clicktobegin, LAYER_FG_TOP);

	title = new Sprite(rm->getImage("images\\title.png"));
	ents->add(title, LAYER_FG_TOP);

	ofDisableAntiAliasing();
	Sprite* plane = new Sprite(rm->getImage("images\\f14.png"));
	ents->add(plane, LAYER_FG_MID);
	plane->setScale(1.5f);
	plane->setAng(93.0f);
	plane->setPos(ofVec2f(127.0f, -200.0f));

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
}

void MenuState::update()
{
	title->setPos(ofVec2f(ofRandomf()*0.65f, titleY + ofRandomf()*0.65f));
	titleY = approach(titleY, titleTargY, (titleTargY - titleY) * 0.025f);

	if (abs(titleTargY - titleY) < 5.0f)
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

	if (input->keyPressed(' '))
	{
		ents->clear();
		//ents->update();
		changeState(new MainStage());
	}
}

void MenuState::draw()
{
	
}
