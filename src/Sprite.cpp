#include "Sprite.h"

Sprite::Sprite()
{
	hasImage = false;
	lifeSpan = -1;
	createTime = ofGetElapsedTimeMillis();
	setID("sprite");
}

Sprite::Sprite(ofImage _image)
{
	setImage(_image);
	lifeSpan = -1;
	createTime = ofGetElapsedTimeMillis();
	setID("sprite");
}

void Sprite::update()
{
	Entity::update();
	if (lifeSpan != -1 && ofGetElapsedTimeMillis() > createTime + lifeSpan)
	{
		remove();
	}
}

void Sprite::draw()
{
	if (hasImage)
	{
		/*
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofPushMatrix();
		ofTranslate(pos);
		ofRotateDeg(ang);
		image.draw(0.0f, 0.0f);
		ofPopMatrix();
		*/
		//std::cout << "test";
		ofSetRectMode(OF_RECTMODE_CENTER);

		ofPushMatrix();
		ofTranslate(pos);
		ofRotateDeg(ang);

		ofEnableAlphaBlending();
		ofSetColor(color, alpha);
		image.draw(0.0f, 0.0f);
		ofDisableAlphaBlending();

		ofPopMatrix();
	}
}

void Sprite::setImage(ofImage _image)
{
	image = _image;
	size = ofVec2f(image.getWidth(), image.getHeight());
	hasImage = true;
}
