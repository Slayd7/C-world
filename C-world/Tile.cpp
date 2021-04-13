#include "pch.h"
#include "Tile.h"

TileRef::TileRef(int newid, LTexture* tex, Vector2D os, float newcost) {
	baseTex = tex;
	clip = new SDL_Rect();
	clip->x = os.x * TILESIZE;
	clip->y = os.y * TILESIZE;
	clip->w = TILESIZE;
	clip->h = TILESIZE;
	id = newid;
	cost = newcost;
}
TileRef::TileRef(TileRef* orig) {
	baseTex = orig->GetTexture();
	clip = orig->clip;
	id = orig->id;
}

Tile::Tile(TileRef* ref, int x, int y)
{
	tileRef = ref;
	pos = Vector2D(x, y);
	cost = ref->GetCost();
	passable = cost == INFINITY ? 50 : 0;
	setPosition(x, y);
}

float Tile::distanceTo(AStarNode* node) const
{
	int newX = m_x - node->getX(), newY = m_y - node->getY();
	return sqrtf(static_cast<float>(newX * newX + newY * newY));
}

float Tile::localDistanceTo(AStarNode* node)
{
	float dist;
	if (node->getX() != m_x && node->getY() != m_y)
		dist = 1.41421356237f;
	else
		dist = 1.0f;
	return dist * cost;
}

void Tile::SetNeighbor(Tile* tile, DIRECTION dir)
{
	neighbors[dir] = tile;
}

Tile* Tile::GetNeighbor(DIRECTION dir)
{
	return neighbors[dir];
}