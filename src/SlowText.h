#pragma once

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
