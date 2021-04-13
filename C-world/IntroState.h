#pragma once
#include "pch.h"
#include "GameEngine.h"
#include "GameState.h"

class IntroState : virtual public GameState
{
public: 
	void Init();
	void Cleanup();
	
	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static IntroState* Instance()
	{
		if (!_mIntroState)
			_mIntroState = new IntroState();
		return _mIntroState;
	}

protected:
	IntroState() {}

private:
	void Transition(GameEngine* game);

	static IntroState* _mIntroState;
	LTexture introTex;

	int x, y;
	//int alpha;
	SDL_Renderer* renderer;
};