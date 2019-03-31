#include "MainStage.h"

void MainStage::setup()
{
	player = new Player(rm->getImage("images\\f14_sheet.png"), input);
	player->setAng(90.0f);
	player->setPos(input->getMouseWorldPos());
	ents->add(player, LAYER_FG_MID);

	for (int i = 0; i < 64; ++i)
	{
		OceanWaves* ow = new OceanWaves();
		ow->setPos(ofVec2f(ofRandomf()*650.0f, ofRandomf()*500.0f));
		ow->setVel(ofVec2f(3.0f, -10.0f));
		ents->add(ow, LAYER_BG_BOTTOM);
	}

	Particle* white = new Particle(ents->rm->getImage("images\\white.png"));
	white->setPos(ofVec2f(0.0f, 0.0f));
	white->setStartScale(30.0f);
	white->setEndScale(30.0f);
	white->setLifespan(2000);
	white->setStartAlpha(600.0f);
	white->setEndAlpha(0.0f);
	white->setColor(ofColor::black);
	ents->add(white, LAYER_FG_TOP);

	SlowText* slowText = new SlowText("International Waters\nBering Sea\nMay 3rd, 1984\n1800 hours", 75);
	slowText->setPos(ofVec2f(-100.0f, 0.0f));
	slowText->lifespan = 8500;
	ents->add(slowText, LAYER_FG_TOP);

	warningSegments[0] = { ofVec2f(-1280.0f / 2.0f + 32.0f, 960.0f / 2.0f - 32.0f), ofVec2f(1280.0f - 64.0f, 0.0f) }; //top
	warningSegments[1] = { ofVec2f(-1280.0f / 2.0f + 32.0f, -960.0f / 2.0f + 32.0f), ofVec2f(1280.0f - 64.0f, 0.0f) }; //bottom
	warningSegments[2] = { ofVec2f(-1280.0f / 2.0f + 32.0f, 960.0f / 2.0f - 32.0f), ofVec2f(0.0f, 960.0f - 64.0f) }; //left
	warningSegments[3] = { ofVec2f(1280.0f / 2.0f - 32.0f, 960.0f / 2.0f - 32.0f), ofVec2f(0.0f, 960.0f - 64.0f) }; //right

	nextEnemySpawnTime = ofGetElapsedTimeMillis() + 8500;

	ofHideCursor();
}

void MainStage::update()
{
	if (ofGetElapsedTimeMillis() > nextEnemySpawnTime)
	{
		Enemy* enemy = new Enemy();
		enemy->setImage(rm->getImage("images\\enemy.png"));
		enemy->setPos(ofVec2f(ofRandomf() * 800.0f, 4000.0f));
		enemy->setAng(-90.0f);
		enemy->setTarget(player);
		ents->add(enemy, LAYER_FG_MID);

		nextEnemySpawnTime = ofGetElapsedTimeMillis() + (int)ofRandom(750.0f);
	}

	if (input->keyPressed(' '))
	{
		std::cout << "Space pressed\n";
	}

	//update radar
	warningPoints.clear();
	for (size_t i = 0; i < ents->entities[LAYER_FG_MID].size(); ++i)
	{
		Entity* curEnt = ents->entities[LAYER_FG_MID][i];
		if (curEnt->getID() == "enemy")
		{

			if (abs(curEnt->getVel().angle(player->getPos() - curEnt->getPos())) > 90.0f) { continue; }
			ofVec2f q = curEnt->getPos();
			ofVec2f s = player->getPos() - curEnt->getPos();

			/*
			ofVec2f p = ofVec2f(-1280.0f / 2.0f + 32.0f, 960.0f / 2.0f - 32.0f);
			ofVec2f r = ofVec2f(1280.0f / 2.0f - 32.0f, 960.0f / 2.0f - 32.0f) - p;
			*/

			for (size_t i = 0; i < warningSegments.size(); ++i)
			{
				ofVec2f p = warningSegments[i].p1;
				ofVec2f r = warningSegments[i].p2;

				float t = cross2d((q - p), s) / cross2d(r, s);
				float u = cross2d((q - p), r) / cross2d(r, s);

				if (cross2d(r, s) != 0 && t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f)
				{
					ofVec2f pt = p + t * r;
					ofColor color;
					float dist = (pt - q).length();
					if (dist < 500.0f)
					{
						color = ofColor::red;
					}
					else
					{
						color = ofColor::yellow;
					}
					warningPoints.push_back({ pt, color, (int)((500000.0f) / (dist + 0.1f)) });
				}
			}

			
		}
	}
}

void MainStage::draw()
{
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Frame Rate: " + std::to_string(ofGetFrameRate()), ofGetWindowWidth() / 2 - 170, ofGetWindowHeight() / 2 - 15);
	ofDrawBitmapString("Entities: " + std::to_string(ents->size()), ofGetWindowWidth() / 2 - 170, ofGetWindowHeight() / 2 - 35);

	ofDrawBitmapString("Score: " + std::to_string(player->score), -ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 - 15);
	ofNoFill();
	ofSetColor(ofColor::white, 100);
	ofDrawRectangle(input->getMouseWorldPos().x, input->getMouseWorldPos().y - 32, 64, 64);

	ofDrawRectangle(0.0f, 0.0f, 1280 - 64, 960 - 64); //radar border

	for (size_t i = 0; i < warningPoints.size(); ++i)
	{
		ofSetColor(warningPoints[i].color, warningPoints[i].alpha);
		//ofDrawBitmapString("WARNING", warningPoints[i].x, warningPoints[i].y);
		rm->getImage("images\\warning.png")->draw(warningPoints[i].pos);
	}

	ofFill();
	ofSetColor(ofColor::white, 50);
	ofDrawRectangle(input->getMouseWorldPos().x, input->getMouseWorldPos().y + 4, 64, 8); //heat meter
	ofSetColor(ofColor::red, 50);
	ofDrawRectangle(input->getMouseWorldPos().x, input->getMouseWorldPos().y+4, 64*(player->heat /100.0f), 8); //heat meter
}
