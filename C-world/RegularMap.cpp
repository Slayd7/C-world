#include "pch.h"
#include "RegularMap.h"

#define NOISESCALE 7


RegularMap::RegularMap() {
	entities = new EntityManager();
}

// RESEARCH AUTOTILING
bool RegularMap::Generate(int seed, AssetManager* assets)
{
	bool success = true;
	if (seed == -1) {
		seed = (int)time(NULL);
		printf("No seed entered - using current time: %i\n", seed);
	}
	
	FastNoise elevation;
	FastNoise moisture;
	elevation.SetNoiseType(FastNoise::NoiseType::Perlin);
	moisture.SetNoiseType(FastNoise::NoiseType::Perlin);
	elevation.SetSeed(seed);
	moisture.SetSeed(seed + 1);


	for (int y = 0; y < MAXMAPSIZEY; y++)
	{
		for (int x = 0; x < MAXMAPSIZEX; x++) {
			
			float val = elevation.GetNoise(x * NOISESCALE, y * NOISESCALE, 0);
			val = val + (0.5 * elevation.GetNoise(x * (2 * NOISESCALE), y * (2 * NOISESCALE), 0));
			val = val + (0.25 * elevation.GetNoise(x * (4 * NOISESCALE), y * (4 * NOISESCALE), 0));
			val += 1;
			val *= 0.5;
			val = IslandMask(val, x, y);
			TileType t = GenerateTileType(val);

			float m = moisture.GetNoise(x * NOISESCALE, y * NOISESCALE, 0);
			m = m + (0.5 * moisture.GetNoise(x * (2 * NOISESCALE), y * (2 * NOISESCALE), 0));
			m = m + (0.25 * moisture.GetNoise(x * (4 * NOISESCALE), y * (4 * NOISESCALE), 0));
			m += 1;
			m *= 0.5;
			m = pow(m, 1.3);
			
			Tile* tile = new Tile(GenerateTileRef(t, m, assets), x, y);
			
			
			Tiles.push_back(tile);
			

		}
	}
	EdgePass(assets);

	// Prepare pathfinding
	int newX, newY;
	Tile* aChild;
	for (int y = 0; y < MAXMAPSIZEY; y++)
	{
		for (int x = 0; x < MAXMAPSIZEX; x++)
		{
			for (int i = -1; i < 2; ++i)
			{
				newX = x + i;
				for (int j = -1; j < 2; ++j) // for all squares in this 3*3 square
				{
					newY = y + j;
					if (newX > -1 && newX < MAXMAPSIZEX && newY > -1 && newY < MAXMAPSIZEY) // be sure not to go outside the limits
					{
						aChild = Tiles.at(newX + (newY * (size_t)MAXMAPSIZEX));
						if (aChild->IsPassable() && ( newX != x || newY != y)) // only take free squares and not the one we are examining
							Tiles.at(x + (y * (size_t)MAXMAPSIZEX))->addChild(aChild, Tiles.at(x + (y * (size_t)MAXMAPSIZEX))->localDistanceTo(aChild));
					}
				}
			}
		}
	}

	

	return success;
}

void RegularMap::EdgePass(AssetManager* assets) {
	/*
	std::vector<int> oldIds;
	for (int x = 0; x < MAXMAPSIZEX; x++)
	{
		for (int y = 0; y < MAXMAPSIZEY; y++) {
			oldIds.push_back(GetTileAt(x, y)->GetID());
		}
	}
	for (int x = 0; x < MAXMAPSIZEX; x++)
	{
		for (int y = 0; y < MAXMAPSIZEY; y++) {
			int sides = 0x0000;
			// 0001  Top
			// 0010  Right
			// 0100  Bottom
			// 1000  Left
			Tile* toCompare = GetTileAt(x, y);
			if (toCompare->GetID() == assets->getTileRefByName("grass")->GetID()) {

				if (x > 0) {
					if (oldIds[(x - 1) + (MAXMAPSIZEX * y)] != toCompare->GetID())
						sides += 0x1000;
				}
				if (x < (MAXMAPSIZEX - 1))
				{
					if (oldIds[(x + 1) + (MAXMAPSIZEX * y)] != toCompare->GetID())
						sides += 0x0010;
				}
				if (y > 0) {
					if (oldIds[x + (MAXMAPSIZEX * (y - 1))] != toCompare->GetID())
						sides += 0x0001;
				}
				if (y < (MAXMAPSIZEY - 1)) {
					if (oldIds[x + (MAXMAPSIZEX * (y + 1))] != toCompare->GetID())
						sides += 0x0100;
				}
			}

			switch (sides) {
			case 0x0001: // top
				SetTileAt(new TileRef(assets->getTileRefByName("sand_grass_top")), x, y);
				break;
			case 0x0010: // right
				SetTileAt(new TileRef(assets->getTileRefByName("sand_grass_right")), x, y);
				break;
			case 0x0100: // bottom
				SetTileAt(new TileRef(assets->getTileRefByName("sand_grass_bottom")), x, y);
				break;
			case 0x1000: // left
				SetTileAt(new TileRef(assets->getTileRefByName("sand_grass_left")), x, y);
				break;
			case 0x0011: // top right
				SetTileAt(new TileRef(assets->getTileRefByName("sand_grass_corner_tr")), x, y);
				break;
			case 0x1001: // top left
				SetTileAt(new TileRef(assets->getTileRefByName("sand_grass_corner_tl")), x, y);
				break;
			case 0x0110: // bottom right
				SetTileAt(new TileRef(assets->getTileRefByName("sand_grass_corner_br")), x, y);
				break;
			case 0x1100: // bottom left
				SetTileAt(new TileRef(assets->getTileRefByName("sand_grass_corner_bl")), x, y);
				break;
			default:
				break;
			}
		}
	}*/
}

std::vector<Tile*> RegularMap::Pathfind(Vector2D start, Vector2D goal)
{
	std::vector<Tile*> path;

	pathfinder.setStart(*Tiles.at((int)start.x + ((int)start.y * (size_t)MAXMAPSIZEX)));
	pathfinder.setGoal(*Tiles.at((int)goal.x + ((int)goal.y * (size_t)MAXMAPSIZEX)));
	pathfinder.findPath<AStar>(path);

	AStar::getInstance().clear();
	
	return path;
}

bool RegularMap::SetTileAt(Tile* t, int x, int y) {
	if (x >= MAXMAPSIZEX || y >= MAXMAPSIZEY) return false;
	Tile* old = Tiles.at(x + (MAXMAPSIZEX * y));
	Tiles.at(x + (MAXMAPSIZEX * y)) = t;
	old->~Tile();
	return true;
}

TileType RegularMap::GenerateTileType(float val) {
	TileType t = TileType::Grass;

	if (val <= 0.03) {
		t = TileType::DeepWater;
	}
	else if (val <= 0.08) {
		t = TileType::Water;
	}
	else if (val <= 0.2) {
		t = TileType::Sand;
	}
	else if (val <= 0.8) {
		t = TileType::Grass;
	}
	return t;
}

TileRef* RegularMap::GenerateTileRef(TileType type, float moisture, AssetManager* assets)
{
	TileRef* t = NULL;
	switch (type) {
	case DeepWater:
		if (moisture <= 0.5) {
			t = assets->getTileRefByName("water");
		}
		else {
			t = assets->getTileRefByName("water");
		}
		break;

	case Water:
		if (moisture <= 0.5) {
			t = assets->getTileRefByName("water");
		}
		else {
			t = assets->getTileRefByName("water");
		}
		break;

	case Sand:
		if (moisture <= 0.5) {
			t = assets->getTileRefByName("sand");
		}
		else {
			t = assets->getTileRefByName("sand");
		}
		break;

	case Grass:
		if (moisture <= 0.35) {
			t = assets->getTileRefByName("grass");
		}
		else if (moisture <= 0.55) {
			t = assets->getTileRefByName("grass");
		}
		else if (moisture <= 0.75) {
			t = assets->getTileRefByName("grass");
		}
		else {
			t = assets->getTileRefByName("grass");
		}
		break;
	case Rock:
		break;
	}
	return t;
}

float RegularMap::IslandMask(float val, int x, int y)
{
	float newx = abs(x - MAXMAPSIZEX * 0.5);
	float newy = abs(y - MAXMAPSIZEY * 0.5);
	newx = newx / (MAXMAPSIZEX * 0.5);
	newy = newy / (MAXMAPSIZEY * 0.5);
	if (newx < newy) newx = newy;

	return (1 - newx) * val;
}
