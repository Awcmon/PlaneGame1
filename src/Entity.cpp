#include "Entity.h"

Entity::Entity(std::string _id, ofVec2f _pos, ofVec2f _scale, float _ang, ofVec2f _vel)
{
	id = _id;
	pos = _pos;
	scale = _scale;
	ang = _ang;
	vel = _vel;
	owner = nullptr;
	color = ofColor(255, 255, 255);
	alpha = 255;
}

//ToDo: Make this framerate independent maybe?
void Entity::update()
{
	pos += vel;
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

//Delete entities that need to be deleted then run update on them
void EntitySystem::update()
{
	if (entities.size() == 0) { return; }

	//delete entities that are to be deleted 
	//pretty much taken from Sprite.cpp from emitterCollision from the class code
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
	ent->setEntitySystem(this);
	entities[layer].push_back(ent);
}

//queue for deletion at the next update
void EntitySystem::remove(Entity * ent)
{
	entitiesToRemove.push_back(ent);
}

void EntitySystem::clear()
{
	for (size_t i = 0; i < entitiesToRemove.size(); ++i)
	{
		delete entitiesToRemove[i];
	}
	entitiesToRemove.clear();

	for (size_t i = 0; i < entities.size(); ++i)
	{
		for (size_t j = 0; j < entities[i].size(); ++j)
		{
			delete entities[i][j];
		}
		entities[i].clear();
	}
	entities.clear();
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
