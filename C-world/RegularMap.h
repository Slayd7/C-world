#pragma once
#include "Map.h"
#include <time.h>
#include <cmath>
#include "external/FastNoise-master/FastNoise.h"
#include "EntityManager.h"

class RegularMap : virtual public Map
{
public:
	RegularMap();
	virtual bool SetTileAt(Tile* t, int x, int y);
	virtual bool Generate(int seed, AssetManager* assets);

	virtual std::vector<Tile*> Pathfind(Vector2D start, Vector2D goal) override;
	// Inherited via Map
	virtual EntityManager* Entities() override {
		return entities;
	};

private:

	virtual TileType GenerateTileType(float val);
	virtual TileRef* GenerateTileRef(TileType type, float moisture, AssetManager* assets);
	float IslandMask(float val, int x, int y);
	void EdgePass(AssetManager* assets);

	EntityManager* entities;

};

