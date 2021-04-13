#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "LTexture.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "Defs.h"
#include "LTimer.h"
#include <thread>

class GameState;

class GameEngine
{
public:
	bool Init(const char* title, int width = 1920, int height = 1080,
		int bpp = 0, bool fullscreen = false);
	void Cleanup();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return _mRunning; }
	void Quit() { _mRunning = false; }

	// Singletons
	static GameEngine* Instance() {
		if (!_mInstance)
			_mInstance = new GameEngine();
		return _mInstance;
	};

	static SDL_Renderer* Renderer() {
		return _mRenderer;
	};

	static SDL_Window* Window() {
		return _mWindow;
	};

	static class AssetManager* Assets() {
		return _mAssets;
	};

	static InputManager* Input() {
		return _mInput;
	};

	static LTimer* Timer() {
		if (!_mTimer)
			_mTimer = new LTimer();
		return _mTimer;
	}


private:
	static GameEngine* _mInstance;
	static SDL_Renderer* _mRenderer;
	static SDL_Window* _mWindow;
	static class AssetManager* _mAssets;
	static InputManager* _mInput;
	static LTimer* _mTimer;

	GameEngine();
	~GameEngine();

	std::vector<GameState*> states;
	bool _mRunning;
	bool _mFullscreen;

};
