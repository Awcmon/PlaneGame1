#include "Debris.h"

void Debris::update()
{
	Sprite::update();

	Particle* smokePuff = new Particle(ents->rm->getImage("images\\smokepuff1.png"));
	//smokePuff->applyForce(ofVec2f(ofRandomf() * 55.0f, -15.0f + ofRandomf() * 55.0f));
	smokePuff->setVel(getVel()*0.5f + ofVec2f(1.0f, 1.0f) * ofRandomf() * 2.0f);
	smokePuff->setAng(ofRandomf()*180.0f);
	smokePuff->setPos(pos);
	smokePuff->setStartScale(0.0f);
	smokePuff->setEndScale(1.0f);
	smokePuff->setLifespan(200);
	smokePuff->setColor(ofColor(1.0f, 1.0f, 1.0f) * 150.0f);
	smokePuff->setStartAlpha(255.0f);
	smokePuff->setEndAlpha(0.0f);
	ents->add(smokePuff, LAYER_FG_BOTTOM);
}
