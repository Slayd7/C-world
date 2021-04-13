#include "pch.h"
#include "Camera.h"
#include "GameEngine.h"
#include <cmath>

Camera::Camera()
{
	maxX = (TILESIZE * MAXMAPSIZEX) - SCREEN_WIDTH;
	maxY = (TILESIZE * MAXMAPSIZEY) - SCREEN_HEIGHT;
	SetZoom(1, Vector2D(0, 0));
	camPos = Vector2D(0, 0);
	midScreen = Vector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

Vector2D Camera::InboundsPosition(Vector2D pos)
{
	int x = pos.x, y = pos.y;
	if (x < -(zoom * TILESIZE))
	{
		x = -(zoom * TILESIZE);
	}
	else if (x > maxX) {
		x = maxX;
	}
	if (y < -(zoom * TILESIZE)) {
		y = -(zoom * TILESIZE);
	}
	else if (y > maxY) {
		y = maxY;
	}

	return Vector2D(x, y);
}

void Camera::MoveStep(int x, int y)
{
	MoveToPosition(camPos.x + x, camPos.y + y);
}

Vector2D Camera::GetVisibleMinimums() {
	Vector2D pos = GridToTile(camPos);
	pos.x--;
	pos.y--;
	pos.x = std::max(pos.x, 0.0);
	
	pos.y = std::max(pos.y, 0.0);

	return pos;
}

Vector2D Camera::GetVisibleMaximums() {
	Vector2D pos = GridToTile(Vector2D(camPos.x + SCREEN_WIDTH + (3 * TILESIZE), camPos.y + SCREEN_HEIGHT + (3 * TILESIZE)));
	pos.x = pos.x >= MAXMAPSIZEX ? MAXMAPSIZEX - 1 : pos.x;
	pos.y = pos.y >= MAXMAPSIZEY ? MAXMAPSIZEY - 1 : pos.y;
	return pos;
}

void Camera::Draw(Map* activeMap)
{
	Vector2D min = GetVisibleMinimums();
	Vector2D max = GetVisibleMaximums();
	for (int x = min.x; x < max.x; x++)
	{
		for (int y = min.y; y < max.y; y++)
		{
			Tile* t = activeMap->GetTileAt(x, y);
			Vector2D p = Vector2D(x * TILESIZE * zoom, y * TILESIZE * zoom);
			p = p - camPos;
			t->GetTexture()->
				render(
					p.x, p.y,
					zoom,
					t->GetClip());
			
		}
	}
	
	activeMap->Entities()->Draw(camPos, zoom, min, max);
	
	for (UIGizmo* g : activeMap->GetGizmos())
	{
		g->Draw(camPos, zoom);
	}
};

LTexture* Camera::GetNumberTex(int num) {
	if (numberTextures[num] == NULL) {
		numberTextures[num] = GameEngine::Assets()->newTextTexture(std::to_string(num), "basic", 1, SDL_Color{ 255,255,255,255 });
	}
	return numberTextures[num];
}

void Camera::SetZoom(double z, Vector2D centeredOn)
{
	if (z < zoomMin) z = zoomMin;
	if (z > zoomMax) z = zoomMax;
	double ratio = z / zoom;
	double scaleChange = zoom - z;
	zoom = z;
	maxX = (TILESIZE * MAXMAPSIZEX) * zoom - SCREEN_WIDTH;
	maxY = (TILESIZE * MAXMAPSIZEY) * zoom - SCREEN_HEIGHT;
	camPos = InboundsPosition((camPos  * ratio) - (centeredOn * scaleChange));
}

void Camera::ZoomStep(int z, Vector2D centeredOn) {
	if (z > 0) {
		SetZoomLevel(zoom + zoomstep, centeredOn);
	}
	else if (z < 0) {
		SetZoomLevel(zoom - zoomstep, centeredOn);
	}
}