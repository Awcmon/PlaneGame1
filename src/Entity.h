#pragma once

#include <vector>
#include <string>
#include "ofMain.h"
#include "ResourceManager.h"

class EntitySystem; //class prototype

//Base class for game objects
//ToDo: Consider some method of static polymorphism?
//Use z position for render order
class Entity
{
public:
	Entity(std::string _id = "entity", glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f), float _ang = 0.0f, glm::vec3 _vel = glm::vec3(0.0f, 0.0f, 0.0f));

	virtual void update();
	virtual void draw();
	void remove();
	void setEntitySystem(EntitySystem* _entSys);
	void setID(std::string _id);
	std::string getID();

	glm::vec3 pos;
	glm::vec3 size;
	glm::vec3 scale;
	glm::vec3 vel;
	float ang;

	std::string id;

protected:
	EntitySystem* ents; //pointer to the entity system to handle deletion
};

//Manages all the entities
//ToDo: Use an object pool instead of a naive vector
class EntitySystem
{
public:
	EntitySystem();
	~EntitySystem();

	void setResourceManager(ResourceManager* _rm);

	void update();
	void draw();
	void add(Entity* ent);
	void remove(Entity* ent);
	void clear(); //deallocates (deletes) all entities.

	std::vector<Entity*> entities;

	ResourceManager* rm;

private:
	std::vector<Entity*> entitiesToRemove;
};
