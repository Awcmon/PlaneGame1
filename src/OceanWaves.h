#pragma once

//Alan Duong, 03/31/19
//Entities that make the blue background look a bit more like an ocean.

#include "ofMain.h"
#include "Sprite.h"

class OceanWaves : public Entity
{
public:
	OceanWaves();
	void update();
	void draw();

	float thickness;
	float maxLength;
	ofVec2f bounds;
	float oscillatorFreq;
	float oscillatorOffset;

	float curLength;

	uint64_t createTime;
};
