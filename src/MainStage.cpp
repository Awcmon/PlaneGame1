#include "MainStage.h"

void MainStage::setup()
{
	player = new Player(rm->getImage("images\\f14_sheet.png"), input);
	player->setAng(90.0f);
	ents->add(player, LAYER_FG_MID);

	for (int i = 0; i < 64; ++i)
	{
		OceanWaves* ow = new OceanWaves();
		ow->setPos(ofVec2f(ofRandomf()*650.0f, ofRandomf()*500.0f));
		ow->setVel(ofVec2f(3.0f, -10.0f));
		ents->add(ow, LAYER_BG_BOTTOM);
	}

	nextEnemySpawnTime = ofGetElapsedTimeMillis() + 2000;

	ofHideCursor();
}

void MainStage::update()
{
	if (ofGetElapsedTimeMillis() > nextEnemySpawnTime)
	{
		Enemy* enemy = new Enemy();
		enemy->setImage(rm->getImage("images\\enemy.png"));
		enemy->setPos(ofVec2f(ofRandomf() * 800.0f, 2000.0f));
		enemy->setAng(-90.0f);
		enemy->setTarget(player);
		ents->add(enemy, LAYER_FG_MID);

		nextEnemySpawnTime = ofGetElapsedTimeMillis() + (int)ofRandom(2000.0f);
	}
}

void MainStage::draw()
{
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Frame Rate: " + std::to_string(ofGetFrameRate()), ofGetWindowWidth() / 2 - 170, ofGetWindowHeight() / 2 - 15);
	ofDrawBitmapString("Entities: " + std::to_string(ents->size()), ofGetWindowWidth() / 2 - 170, ofGetWindowHeight() / 2 - 35);
}
