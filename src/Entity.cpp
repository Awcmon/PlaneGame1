#include "Entity.h"

Entity::Entity(std::string _id, glm::vec3 _pos, glm::vec3 _scale, float _ang, glm::vec3 _vel)
{
	id = _id;
	pos = _pos;
	scale = _scale;
	ang = _ang;
	vel = _vel;
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



EntitySystem::EntitySystem()
{
}

//On destruct, clear all entities held by the system
EntitySystem::~EntitySystem()
{
	clear();
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
		entities.erase(std::remove(entities.begin(), entities.end(), entitiesToRemove[i]), entities.end());
		delete entitiesToRemove[i];
	}
	entitiesToRemove.clear();

	//update the remaining entities
	for (size_t i = 0; i < entities.size(); ++i)
	{
		entities[i]->update();
	}
}

//draw all entities
void EntitySystem::draw()
{
	for (size_t i = 0; i < entities.size(); ++i)
	{
		//std::cout << "draw" << i << "\n";
		entities[i]->draw();
	}
}

//add entity to the system
void EntitySystem::add(Entity* ent)
{
	//std::cout << "added\n";
	ent->setEntitySystem(this);
	entities.push_back(ent);
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
		delete entities[i];
	}
	entities.clear();
}
