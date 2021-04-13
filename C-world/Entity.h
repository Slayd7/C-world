#pragma once
#include "pch.h"
#include "LTexture.h"
#include "Defs.h"
#include <vector>
#include "Map.h"

class Entity
{
public:
	//virtual void Init() = 0;


	void setTexture(LTexture* tex);

	Vector2D GetScreenPosition() { return position; };
	Vector2D GetTilePosition() { return Vector2D(occupiedTile->getX(), occupiedTile->getY()); }

	virtual void SetScreenPosition(Vector2D newPos) { position = newPos; };
	virtual void SetTilePosition(Vector2D newPos) 
	{ 
		position = newPos * TILESIZE; 
		if (currentMap != NULL)
		{
			occupiedTile = currentMap->GetTileAt(newPos);
		}
	}

	virtual void Tick() = 0;
	virtual void Draw(Vector2D camPos, double zoom) = 0;


	void SetWidth(int width);
	void SetHeight(int height);

	std::string GetName() { return name; }
	void SetName(std::string newname) { name = newname; }

	std::vector<std::string> GetTags() { return tags; }
	void AddTag(std::string newtag) { tags.push_back(newtag); }

	void SetMap(Map* map) { currentMap = map; }
	Map* GetMap() { return currentMap; }

	void OccupyTile();

	bool IsPassable() { return passable; };


protected:

	Vector2D position, 
			 size = Vector2D(1,1);
			 // size = size in tiles of entity 
			 // i.e. a bed might be 1x2 tiles, that's the size
	

	LTexture* texture;
	SDL_Rect* clip;
	int offsetw, offseth;	// Render offset, i.e.:  
							// (position.x * TILESIZE + offsetw) * ZOOM

	std::string name;			   // Name of entity
	std::vector<std::string> tags; // For search indexing, etc

	Map* currentMap;	// Map entity is on
	Tile* occupiedTile; // Tile that entity is currently occupying
	struct {
		int x;
		int y;
	} tileCoords;

	bool passable; // Is this entity passable?

	double Distance(Entity* other)
	{
		return sqrt(pow((position.x - other->position.x), 2.0) + pow((position.y - other->position.y), 2.0));
	}

	double Distance(Vector2D other)
	{
		return sqrt(pow((position.x - other.x), 2.0) + pow((position.y - other.y),2.0));
	}

};
