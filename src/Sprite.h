#pragma once

//Alan Duong, 03/31/19
//An entity that has an image, animated or not.

#include "ofMain.h"
#include "Entity.h"

struct AnimData
{
	int period;
	std::vector<int> frameSeq;
};

//Anything that is drawn with an image.
class Sprite : public Entity
{
public:
	Sprite();
	void init();
	Sprite(ofImage* _image);
	virtual void update();
	virtual void draw();
	void setImage(ofImage* _image);

	void slice(int _numRows, int _numCols);
	void setFrame(int _frameNumber);
	void setAnim(std::string _anim);

	void setLifespan(int _lifespan);

	ofImage* image;
	bool hasImage;

	ofVec2f sheetSize;
	int numRows;
	int numCols;
	int frameNumber;
	std::string curAnim;
	std::unordered_map<std::string, AnimData> anims;
	int seqInd;
	uint64_t lastAnimTime;
};
