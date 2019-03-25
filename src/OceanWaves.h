#pragma once

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
