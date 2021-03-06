#include "Entity.h"

//Alan Duong, 03/31/19
//An entity class from which all game objects inherit from.
//The physics stuff is done here.

Entity::Entity(std::string _id, ofVec2f _pos, float _scale, float _ang, ofVec2f _vel)
{
	id = _id;
	pos = _pos;
	scale = _scale;
	ang = _ang;
	vel = _vel;
	owner = nullptr;
	color = ofColor(255, 255, 255);
	alpha = 255;
	mass = 1.0f;
	accel = ofVec2f(0.0f, 0.0f);
	angVel = 0.0f;

	lifespan = -1;
	createTime = ofGetElapsedTimeMillis();
}

//ToDo: Make this framerate independent maybe?
void Entity::update()
{

	if (lifespan != -1 && ofGetElapsedTimeMillis() > createTime + lifespan)
	{
		remove();
	}

	//float dt = 1.0 / ofGetFrameRate();
	float dt = 1.0f; //we are capped to 60 fps anyways

	pos += vel * dt;
	vel += accel * dt;
	//std::cout << pos << "\n";
	accel = ofVec2f(0.0f, 0.0f); //clear accel/forces. a continuous force must be applied each frame.

	ang += angVel * dt;
}

void Entity::draw()
{

}

//tell the entity system this belongs to to remove this entity next update
void Entity::remove()
{
	ents->remove(this);
}

void Entity::setEntitySystem(EntitySystem* _entSys)
{
	ents = _entSys;
}

void Entity::setID(std::string _id)
{
	id = _id;
}

std::string Entity::getID()
{
	return id;
}

Entity * Entity::getOwner()
{
	return owner;
}

void Entity::setOwner(Entity * _owner)
{
	owner = _owner;
}

void Entity::setVel(ofVec2f _vel)
{
	vel = _vel;
}

ofVec2f Entity::getVel()
{
	return vel;
}

void Entity::setAng(float _ang)
{
	ang = _ang;
}

float Entity::getAng()
{
	return ang;
}

void Entity::setPos(ofVec2f _pos)
{
	pos = _pos;
}

ofVec2f Entity::getPos()
{
	return pos;
}

ofVec2f Entity::toWorld(ofVec2f _localpos)
{
	return pos + _localpos.rotate(ang);
}

void Entity::setScale(float _scale)
{
	scale = _scale;
}

void Entity::setAlpha(float _alpha)
{
	alpha = _alpha;
}

void Entity::applyForce(ofVec2f _force)
{
	accel += _force * (1.0f / mass);
}

void Entity::setAngVel(float _angVel)
{
	angVel = _angVel;
}

void Entity::setColor(ofColor _color)
{
	color = _color;
}

ofVec2f Entity::forward()
{
	return ofVec2f(1.0f, 0.0f).getRotated(ang);
}



EntitySystem::EntitySystem()
{
	init();
}

//On destruct, clear all entities held by the system
EntitySystem::~EntitySystem()
{
	clear();
}

void EntitySystem::init(int numLayers)
{
	entities.resize(numLayers, {});
}

void EntitySystem::setResourceManager(ResourceManager* _rm)
{
	rm = _rm;
}

void EntitySystem::setView(View * _view)
{
	view = _view;
}

//Delete entities that need to be deleted then run update on them
void EntitySystem::update()
{
	if (entities.size() == 0) { return; }

	//delete entities that are to be deleted 
	//pretty much taken from Sprite.cpp from emitterCollision from the class code
	/*
	for (size_t i = 0; i < entitiesToRemove.size(); i++)
	{
		//std::cout << "deleted\n";
		for (size_t j = 0; j < entities.size(); j++)
		{
			entities[j].erase(std::remove(entities[j].begin(), entities[j].end(), entitiesToRemove[i]), entities[j].end());
		}
		delete entitiesToRemove[i];
	}
	entitiesToRemove.clear();
	*/

	for (const auto& entToRemove : entitiesToRemove) {
		for (size_t j = 0; j < entities.size(); j++)
		{
			entities[j].erase(std::remove(entities[j].begin(), entities[j].end(), entToRemove), entities[j].end());
		}
		delete entToRemove;
	}
	entitiesToRemove.clear();

	//add the entities to add
	for (size_t i = 0; i < entitiesToAdd.size(); ++i)
	{
		AddInfo addInfo = entitiesToAdd[i];
		addInfo.ent->setEntitySystem(this);
		entities[addInfo.layer].push_back(addInfo.ent);
	}
	entitiesToAdd.clear();

	//update the remaining entities
	for (size_t i = 0; i < entities.size(); ++i)
	{
		for (size_t j = 0; j < entities[i].size(); ++j)
		{
			entities[i][j]->update();
		}
	}
}

//draw all entities
void EntitySystem::draw()
{
	//update the remaining entities
	for (size_t i = 0; i < entities.size(); ++i)
	{
		for (size_t j = 0; j < entities[i].size(); ++j)
		{
			entities[i][j]->draw();
		}
	}
}

//add entity to the system
void EntitySystem::add(Entity* ent, int layer)
{
	//std::cout << "added\n";
	/*
	ent->setEntitySystem(this);
	entities[layer].push_back(ent);
	*/

	entitiesToAdd.push_back({ ent, layer });
}

//queue for deletion at the next update
void EntitySystem::remove(Entity * ent)
{
	entitiesToRemove.insert(ent);
}

void EntitySystem::clear()
{
	/*
	for (size_t i = 0; i < entitiesToRemove.size(); ++i)
	{
		delete entitiesToRemove[i];
	}
	*/
	entitiesToRemove.clear();

	for (size_t i = 0; i < entities.size(); ++i)
	{
		for (size_t j = 0; j < entities[i].size(); ++j)
		{
			delete entities[i][j];
		}
		entities[i].clear();
	}
	//entities.clear();
}

size_t EntitySystem::size()
{
	size_t sum = 0;
	for (size_t i = 0; i < entities.size(); ++i)
	{
		sum += entities[i].size();
	}
	return sum;
}
