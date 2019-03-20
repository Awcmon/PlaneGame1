#pragma once

#include "ofMain.h"
#include "Entity.h"

//Anything that is drawn with an image.
class Sprite : public Entity
{
public:
	Sprite();
	Sprite(ofImage _image);
	virtual void update();
	virtual void draw();
	void setImage(ofImage _image);

	ofImage image;
	bool hasImage;

	int lifeSpan; //in millis
	uint64_t createTime;
};
