#pragma once

#include "pch.h"
#include <SDL_events.h>
#include "Camera.h"
#include "UI.h"

class InputManager
{
public:
	InputManager();
	void SetCamera(Camera* cam);
	void SetMap(Map* newmap);
	int HandleEvents(SDL_Event event);

private:

	Camera* activeCam;
	Map* activeMap;

	Vector2D startPos;
	bool firstEntered;

	bool lmbHeld = false;
	bool rmbHeld = false;
	bool mmbHeld = false;
};

