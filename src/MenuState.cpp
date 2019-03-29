#include "MenuState.h"

void MenuState::setup()
{

}

void MenuState::update()
{
	if (input->keyPressed(' '))
	{
		changeState(new MainStage());
	}
}

void MenuState::draw()
{

}
