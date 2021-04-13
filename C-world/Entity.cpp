#include "pch.h"
#include "Entity.h"

/// <summary>
/// Sets the texture of the entity
/// </summary>
/// <param name="tex">LTexture that the entity will use</param>
void Entity::setTexture(LTexture* tex) {
	texture = tex;
	clip = new SDL_Rect();
	clip->x = 0;
	clip->y = 0;

	clip->w = tex->getWidth();
	clip->h = tex->getHeight();
}

/// <summary>
/// Sets width of this entity, in pixels. Also sets the offset,
/// which offsets the drawn texture within its tile, in case the LTex is not the same size as TILESIZE.
/// </summary>
/// <param name="width">Width of entity's texture, in pixels</param>
void Entity::SetWidth(int width) {
	clip->w = width;
	int ow = (TILESIZE - width) * 0.5f;
	if (ow > 0) offsetw = ow;
	else offsetw = 0;
}

/// <summary>
/// Sets height of this entity, in pixels. Also sets the offset,
/// which offsets the drawn texture within its tile, in case the LTex is not the same size as TILESIZE.
/// </summary>
/// <param name="width">Height of entity's texture, in pixels</param>
void Entity::SetHeight(int height) {
	clip->h = height;
	int oh = (TILESIZE - height) * 0.5f;
	if (oh > 0) offseth = oh;
	else offseth = 0;
}

/// <summary>
/// Tells a tile that this entity is now occupying it, as well as any tiles within the rectangle
/// of size Entity::size.x by Entity::size.y.
/// </summary>
void Entity::OccupyTile() {
	Tile* baseTile = currentMap->GetTileAt(position / TILESIZE);
	// For some reason this is too much of a puzzle for me right now, i dunno
	// I'll come back to this later
	// Need to Tile::AddEntity() to all tiles starting from baseTile, 
	// in a rectangle of size.x by size.y tiles
}