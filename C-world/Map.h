#pragma once

#include "Tile.h"
#include "Defs.h"
#include <utility>
#include "AssetManager.h"
#include "external/PathFinder-master/src/PathFinder.h"
#include "UIGizmo.h"
#include "Gizmo_Line.h"

class EntityManager;

class Map
{
public:
		
	virtual Tile* GetTileAt(int x, int y) { 
		if (x >= MAXMAPSIZEX || y >= MAXMAPSIZEY) return NULL;
		return Tiles.at(x + (MAXMAPSIZEX * y));
	}
	virtual Tile* GetTileAt(Vector2D pos) {
		if ((int)pos.x >= MAXMAPSIZEX || (int)pos.y >= MAXMAPSIZEY) return NULL;
		return Tiles.at((int)pos.x + (MAXMAPSIZEX * (int)pos.y));
	}
	virtual bool SetTileAt(Tile* t, int x, int y) = 0;
	virtual bool Generate(int seed, AssetManager* assets) = 0;
	virtual std::vector<UIGizmo*> GetGizmos() { return Gizmos; }
	virtual void AddGizmo(UIGizmo* g) { Gizmos.push_back(g); }
	
	virtual std::vector<Tile*> Pathfind(Vector2D start, Vector2D goal) = 0;
	virtual EntityManager* Entities() = 0; // One manager per map


protected:
	virtual TileType GenerateTileType(float val) = 0;
	virtual TileRef* GenerateTileRef(TileType type, float moisture, AssetManager* assets) = 0;
	PathFinder<Tile> pathfinder;

	std::vector<Tile*> Tiles;
	std::vector<UIGizmo*> Gizmos;

};

