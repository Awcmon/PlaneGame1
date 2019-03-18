#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	ofDirectory imagesDir("images");
	//only show png files
	imagesDir.allowExt("png");
	//populate the directory object
	imagesDir.listDir();

	//go through and print out all the paths
	for (size_t i = 0; i < imagesDir.size(); i++) {
		std::cout << (imagesDir.getPath(i)) << "\n";
		ofImage temp;
		temp.load(imagesDir.getPath(i));
		images[imagesDir.getPath(i)] = temp;
	}

	ofDirectory soundsDir("sounds");
	//only show png files
	soundsDir.allowExt("wav");
	//populate the directory object
	soundsDir.listDir();

	//go through and print out all the paths
	for (size_t i = 0; i < soundsDir.size(); i++) {
		std::cout << (soundsDir.getPath(i)) << "\n";
		ofSoundPlayer temp;
		temp.setMultiPlay(true);
		temp.load(soundsDir.getPath(i));
		sounds[soundsDir.getPath(i)] = temp;
	}
}

ofImage ResourceManager::getImage(std::string path)
{
	return images[path];
}

ofSoundPlayer ResourceManager::getSound(std::string path)
{
	return sounds[path];
}
