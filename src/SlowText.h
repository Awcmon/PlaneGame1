#pragma once

//Alan Duong, 03/31/19
//An entity that prints text onto the screen slowly and makes typewriter sounds.

#include "Entity.h"

class SlowText : public Entity
{
public:
	SlowText(std::string _text, int _period);
	void update();
	void draw();

	std::string text;
	std::string curText;
	int iter;
	int period;
	uint64_t lastPrintTime;
};
