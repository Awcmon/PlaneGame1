#include "SlowText.h"

//Alan Duong, 03/31/19
//An entity that prints text onto the screen slowly and makes typewriter sounds.

SlowText::SlowText(std::string _text, int _period)
{
	text = _text;
	period = _period;
	curText = "";
	iter = 0;
	lastPrintTime = 0;
}

void SlowText::update()
{
	Entity::update();
	if (ofGetElapsedTimeMillis() > lastPrintTime + period && iter < text.length())
	{
		curText += text[iter];
		iter++;
		ents->rm->getSound("sounds\\typewriter.wav")->play();
		lastPrintTime = ofGetElapsedTimeMillis();
	}
}

void SlowText::draw()
{
	ofSetColor(ofColor::white, 255.0f);
	ofDrawBitmapString(curText, pos.x, pos.y);
}
