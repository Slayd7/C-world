#include "EntityManager.h"

void EntityManager::Tick()
{
	for (Actor* a : actors)
	{
		a->Tick();
	}
}

void EntityManager::AddEntity(Entity* e)
{
	entities.push_back(e);
	for (std::string str : e->GetTags())
	{
		std::map<std::string, std::vector<Entity*>>::iterator it;
		it = entitiesByTag.find(str);
		if (it == entitiesByTag.end())
		{
			std::vector<Entity*> newEnVec;
			entitiesByTag.insert(std::pair<std::string, std::vector<Entity*>>(str, newEnVec));
			it = entitiesByTag.find(str);
		}
		else {
			it->second.push_back(e);
		}
	}


	if (typeid(*e) == typeid(Actor)) {
		actors.push_back(dynamic_cast<Actor*>(e));
		printf("Added actor: ");
		printf(e->GetName().c_str());
		printf("\n");
	}

	else {
		printf("Added non-actor\n");
	}
}

void EntityManager::Draw(Vector2D camPos, double zoom, Vector2D min, Vector2D max)
{
	for (Entity* e : entities)
	{
		e->Draw(camPos, zoom);
	}

}
