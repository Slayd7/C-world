#pragma once
#include "pch.h"
#include "Defs.h"
#include <vector>
#include <map>
#include <typeinfo>
#include "Entity.h"
#include "Actor.h"

class EntityManager
{
public:
	EntityManager() {}

	void Tick();

	void AddEntity(Entity* e);

	void Draw(Vector2D camPos, double zoom, Vector2D min, Vector2D max);
	

private:
	std::vector<Entity*> entities;
	std::vector<Actor*> actors;
	std::map<std::string, std::vector<Entity*>> entitiesByTag;
};

