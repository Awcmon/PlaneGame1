#include "Sprite.h"
#include "OceanWaves.h"

OceanWaves::OceanWaves()
{
	thickness = 4.0f;
	maxLength = 48.0f;
	setAlpha(100.0f);
	bounds = ofVec2f(1280.0f, 960.0f)*0.5;
	createTime = ofGetElapsedTimeMillis();

	oscillatorFreq = (ofRandomf()+1.0f) * 1.0f;
	oscillatorOffset = ofRandom(100);
	curLength = 0.0f;
}

void OceanWaves::update()
{
	Entity::update();
	if (pos.x > bounds.x)
	{
		pos.x = -bounds.x + ofRandomf() * 50.0f;
	}

	if (pos.y < -bounds.y)
	{
		pos.y = bounds.y + ofRandomf() * 50.0f;
	}

	curLength = maxLength * (sinf(oscillatorFreq*ofGetElapsedTimef() + oscillatorOffset) + 1.0f)*0.5f;
}

void OceanWaves::draw()
{
	ofSetRectMode(OF_RECTMODE_CENTER);

	ofPushMatrix();
	ofTranslate(pos);
	ofRotateDeg(ang);

	ofScale(scale);

	ofEnableAlphaBlending();
	ofSetColor(color, alpha);
	ofDrawRectangle(pos.x + curLength/2.0f, pos.y, curLength, thickness);
	ofDisableAlphaBlending();

	ofPopMatrix();
}
