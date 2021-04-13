#pragma once
#include "pch.h"
#include "GameEngine.h"
#include "GameState.h"
#include "Camera.h"
#include "RegularMap.h"
#include "UI.h"
#include "LTimer.h"
#include "Actor.h"

class PlayState : virtual public GameState
{
public: 
	void Init();
	void Cleanup();
	
	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static PlayState* Instance()
	{
		if (!_mPlayState)
			_mPlayState = new PlayState();
		return _mPlayState;
	}

protected:
	PlayState() {}

private:
	static PlayState* _mPlayState;
	Map* activeMap;
	Camera* activeCam;
	SDL_Renderer* renderer;
	InputManager* input;
	UI* ingameUI;
	LTimer* timer;

	int lastTick = 0;
	int gameSpeed = 0;
	int tick = 0;
};