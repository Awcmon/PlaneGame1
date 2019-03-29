#include "MenuState.h"

void MenuState::setup()
{

	Sprite* carrier = new Sprite(rm->getImage("images\\carrier.png"));
	ents->add(carrier, LAYER_BG_TOP);

	for (int i = 0; i < 64; ++i)
	{
		OceanWaves* ow = new OceanWaves();
		ow->setPos(ofVec2f(ofRandomf()*650.0f, ofRandomf()*500.0f));
		ow->setVel(ofVec2f(3.0f, -3.0f));
		ents->add(ow, LAYER_BG_BOTTOM);
	}
}

void MenuState::update()
{
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
