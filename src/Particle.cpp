#include "Particle.h"

Particle::Particle(ofImage _image)
{
	setImage(_image);
	lifespan = 1000;
	createTime = ofGetElapsedTimeMillis();

	startScale = 1.0f;
	endScale = 1.0f;
	startAlpha = 255.0f;
	endAlpha = 255.0f;
}

void Particle::setStartScale(float _startScale)
{
	startScale = _startScale;
	scale = startScale;
}

void Particle::setEndScale(float _endScale)
{
	endScale = _endScale;
}

void Particle::setStartAlpha(float _startAlpha)
{
	startAlpha = _startAlpha;
	alpha = startAlpha;
}

void Particle::setEndAlpha(float _endAlpha)
{
	endAlpha = _endAlpha;
}

void Particle::update()
{
	Sprite::update();

	float lifePercentage = ((float)(ofGetElapsedTimeMillis() - createTime)) / ((float)lifespan);
	//std::cout << lifePercentage << "\n";
	scale = startScale + (endScale - startScale) * lifePercentage;
	alpha = (int)(startAlpha + (endAlpha - startAlpha) * lifePercentage);
}
