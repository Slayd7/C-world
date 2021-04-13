#include "pch.h"
#include "GameEngine.h"
#include "GameState.h"

GameEngine* GameEngine::_mInstance;
SDL_Renderer* GameEngine::_mRenderer;
SDL_Window* GameEngine::_mWindow;
AssetManager* GameEngine::_mAssets;
LTimer* GameEngine::_mTimer;

GameEngine::GameEngine()
{
	_mFullscreen = false;
	_mRunning = true;
}
GameEngine::~GameEngine()
{
	//Destroy window
	SDL_DestroyRenderer(Renderer());
	SDL_DestroyWindow(Window());
	
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool GameEngine::Init(const char* title, int width, int height,
	int bpp, bool fullscreen)
{
	bool success = true;
	int flags = SDL_WINDOW_SHOWN;

	if (fullscreen) flags += SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		_mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height, flags);
		if (!_mWindow)
		{
			printf("SDL Window could not initialize! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {

			_mRenderer = SDL_CreateRenderer(_mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (!Renderer())
			{
				printf("SDL Renderer could not initialize! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(Renderer(), 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf error: %s\n", TTF_GetError());
				}
			}

			_mFullscreen = fullscreen;
			_mRunning = true;

			printf("GameEngine Init\n");
			_mAssets = new AssetManager();
			if (!_mAssets->init()) success = false;

			//_mInput = new InputManager();
		}
	}

	srand(time(NULL));
	
	return success;
}

void GameEngine::Cleanup()
{
	// cleanup the all states
	while (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// switch back to windowed mode so other 
	// programs won't get accidentally resized
	if (_mFullscreen) {
		//screen = SDL_SetVideoMode(640, 480, 0, 0);
	}

	printf("GameEngine Cleanup\n");

	// shutdown SDL
	SDL_Quit();
}

void GameEngine::ChangeState(GameState* state)
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}


void GameEngine::HandleEvents()
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void GameEngine::Update()
{
	// let the state update the game
	states.back()->Update(this);
}

void GameEngine::Draw()
{
	// let the state draw the screen
	states.back()->Draw(this);
}