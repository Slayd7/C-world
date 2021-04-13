#pragma once
#include "Defs.h"
#include "Map.h"


class Camera
{
public:
	Camera();


	Vector2D GetCameraPosition() { return camPos; };
	Vector2D InboundsPosition(Vector2D pos);

	float GetZoomLevel() { return zoom; }
	void SetZoomLevel(double z, Vector2D centeredOn) { SetZoom(z, centeredOn); }
	void ZoomStep(int z, Vector2D centeredOn);

	Vector2D GetVisibleMinimums();
	Vector2D GetVisibleMaximums();

	void MoveStep(int x, int y);
	void MoveToPosition(int x, int y) { camPos = InboundsPosition(Vector2D(x, y)); }

	Vector2D TileToGrid(Vector2D pos) { return pos * (TILESIZE * zoom); };
	Vector2D GridToTile(Vector2D pos) { return pos / (TILESIZE * zoom); };
	Vector2D ScreenToGrid(Vector2D pos) { return pos + camPos; }
	Vector2D ScreenToTile(Vector2D pos) {
		return Vector2D((int)pos.x + (int)camPos.x, (int)pos.y + (int)camPos.y) / (TILESIZE * zoom);
	}
	

	void Draw(Map* activeMap);


private:
	int maxX, maxY;

	double zoomstep = 6 * (1 / (double)TILESIZE);
	double zoom;
	float zoomMin = 15 * (1 / (double)TILESIZE), zoomMax = 175 * (1 / (double)TILESIZE);
	Vector2D midScreen;
	
	void SetZoom(double z, Vector2D centeredOn);

	LTexture* GetNumberTex(int num);
	std::map<int, LTexture*> numberTextures;

	Vector2D camPos;

};