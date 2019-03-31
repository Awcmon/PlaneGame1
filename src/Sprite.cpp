#include "Sprite.h"

Sprite::Sprite()
{
	hasImage = false;
	init();
}

Sprite::Sprite(ofImage* _image)
{
	setImage(_image);
	init();
}

void Sprite::init()
{
	lifespan = -1;
	createTime = ofGetElapsedTimeMillis();
	setID("sprite");
	curAnim = "idle";
}

void Sprite::update()
{
	Entity::update();

	//animation stuff
	AnimData curAnimData = anims[curAnim];
	if (ofGetElapsedTimeMillis() > lastAnimTime + curAnimData.period)
	{
		seqInd = (seqInd + 1) % curAnimData.frameSeq.size();
		lastAnimTime = ofGetElapsedTimeMillis();
		frameNumber = curAnimData.frameSeq[seqInd];
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

		ofScale(scale);

		ofEnableAlphaBlending();
		ofSetColor(color, alpha);
		//image->draw(0.0f, 0.0f);
		image->drawSubsection(0.0f, 0.0f, size.x, size.y, size.x*(frameNumber % numCols), size.y*(frameNumber / numCols));
		ofDisableAlphaBlending();

		ofPopMatrix();
	}
}

void Sprite::setImage(ofImage* _image)
{
	image = _image;
	sheetSize = ofVec2f(image->getWidth(), image->getHeight());
	hasImage = true;

	slice(1, 1); //assume it is not a sprite sheet.
	anims["idle"] = { 100000000, {0} }; //set a default anim
	setAnim("idle"); //set to default idle anim
}

void Sprite::slice(int _numRows, int _numCols)
{
	numRows = _numRows;
	numCols = _numCols;
	sheetSize = ofVec2f(image->getWidth(), image->getHeight());
	size = ofVec2f(sheetSize.x / numCols, sheetSize.y / numRows);
	frameNumber = 0;
}

void Sprite::setFrame(int _frameNumber)
{
	frameNumber = _frameNumber;
}

void Sprite::setAnim(std::string _anim)
{
	if (curAnim != _anim)
	{
		curAnim = _anim;
		seqInd = 0;
		lastAnimTime = ofGetElapsedTimeMillis();
		frameNumber = anims[curAnim].frameSeq[seqInd];
	}
}

void Sprite::setLifespan(int _lifespan)
{
	lifespan = _lifespan;
}
