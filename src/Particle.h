#pragma once

//Alan Duong, 03/31/19
//Entities that change scale and alpha over time, typically used for particles.

#include "Sprite.h"

class Particle : public Sprite
{
public:
	Particle(ofImage* _image);
	void setStartScale(float _startScale);
	void setEndScale(float _endScale);
	void setStartAlpha(float _startAlpha);
	void setEndAlpha(float _endAlpha);

	void update();
	
	float startScale;
	float endScale;
	float startAlpha;
	float endAlpha;
};