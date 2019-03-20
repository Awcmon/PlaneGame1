#pragma once

#include <vector>
#include <string>

#include "ofMain.h"
#include "ResourceManager.h"

//Define some basic layers.
#define LAYER_BG_BOTTOM 0
#define LAYER_BG_TOP 1
#define LAYER_FG_BOTTOM 2
#define LAYER_FG_MID 3
#define LAYER_FG_TOP 4

class EntitySystem; //class prototype

//Base class for game objects
//ToDo: Consider some method of static polymorphism?
//Use z position for render order
class Entity
{
public:
	Entity(std::string _id = "entity", ofVec2f _pos = ofVec2f(0.0f, 0.0f), ofVec2f _scale = ofVec2f(1.0f, 1.0f), float _ang = 0.0f, ofVec2f _vel = ofVec2f(0.0f, 0.0f));

	virtual void update();
	virtual void draw();
	void remove();
	void setEntitySystem(EntitySystem* _entSys);
	void setID(std::string _id);
	std::string getID();
	Entity* getOwner();
	void setOwner(Entity* _owner);
	void setVel(ofVec2f _vel);
	ofVec2f getVel();
	void setAng(float _ang);
	float getAng();
	void setPos(ofVec2f _pos);
	ofVec2f getPos();
	ofVec2f toWorld(ofVec2f _localpos);

	ofVec2f pos;
	ofVec2f size;
	ofVec2f scale;
	ofVec2f vel;
	float ang;
	ofColor color;
	int alpha;
	
	Entity* owner;

	std::string id;

protected:
	EntitySystem * ents; //pointer to the entity system to handle deletion
};

//Manages all the entities
//ToDo: Use an object pool instead of a naive vector
class EntitySystem
{
public:
	EntitySystem();
	~EntitySystem();

	void init(int numLayers = 5);

	void setResourceManager(ResourceManager* _rm);

	void update();
	void draw();
	void add(Entity* ent, int layer = 0); //the layer determines render order. higher layer has higher priority.
	void remove(Entity* ent);
	void clear(); //deallocates (deletes) all entities.
	size_t size();

	std::vector<std::vector<Entity*>> entities;

	ResourceManager* rm;

private:
	std::vector<Entity*> entitiesToRemove;
};
