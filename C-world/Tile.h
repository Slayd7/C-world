#pragma once
#include "Defs.h"
#include "LTexture.h"
#include "external/PathFinder-master/src/AStar.h"

class Entity;

class TileRef
{
public:
	TileRef(int newid, LTexture* tex, Vector2D os, float newcost);
	TileRef(TileRef* orig);

	TileRef() {}

	LTexture* GetTexture() { return baseTex; }
	SDL_Rect* clip;
	int GetID() { return id; }	
	float GetCost() { return cost; }
	
private:
	LTexture* baseTex;
	int id;
	float cost;
};


class Tile : public AStarNode
{
public:
	Tile(TileRef* ref, int x, int y);
	~Tile() {};
	LTexture* GetTexture() { return tileRef->GetTexture(); }

	SDL_Rect* GetClip() { return tileRef->clip; }

	void SetCost(float c) {	cost = c; }
	float GetCost() { return cost; }
	virtual float distanceTo(AStarNode* node) const override;

	float localDistanceTo(AStarNode* node);

	Vector2D GetPos() { return pos; }

	bool IsPassable() { return passable == 0; }

	void AddEntity(Entity* e, bool canPass)
	{
		entities.push_back(e);
		if (!canPass) passable++;
	}

	void RemoveEntity(Entity* o)
	{
		auto e = entities.begin();
		while (e != entities.end())
		{
			if (*e == o)
			{
				entities.erase(e);
				break;
			}
			e++;
		}
	}

	void SetNeighbor(Tile* tile, DIRECTION dir);
	Tile* GetNeighbor(DIRECTION dir);

private:
	TileRef* tileRef;
	Vector2D pos;

	float cost;
	int passable; // If 0, then is passable. 
				  // Entities add one to passable to keep track of multiple entities on one tile

	Tile* neighbors[8];
	std::vector<Entity*> entities;

};
