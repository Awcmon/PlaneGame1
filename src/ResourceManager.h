#pragma once

#include <unordered_map>
#include <string>
#include "ofMain.h"

class ResourceManager
{
public:
	ResourceManager();
	ofImage* getImage(std::string path);
	ofSoundPlayer* getSound(std::string path);

	std::unordered_map<std::string, ofImage> images;
	std::unordered_map<std::string, ofSoundPlayer> sounds;
};