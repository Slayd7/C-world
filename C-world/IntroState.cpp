#include "pch.h"
#include "IntroState.h"
#include "PlayState.h"

IntroState* IntroState::_mIntroState;

void IntroState::Init()
{
	//_mIntroState = new IntroState();

	introTex = *GameEngine::Assets()->newTextTexture("C-World", "rns", 5, SDL_Color{ 255,255,255,255 });
	renderer = GameEngine::Renderer();
	x = (1920 / 2) - (introTex.getWidth() / 2);
	y = (1080 / 2) - (introTex.getHeight() / 2);
}

void IntroState::Cleanup()
{
}

void IntroState::Pause()
{
}

void IntroState::Resume()
{
	
}

void IntroState::HandleEvents(GameEngine* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			game->Quit();
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				Transition(game);
				break;

			case SDLK_ESCAPE:
				game->Quit();
				break;
			}
			break;
		}
	}
}

void IntroState::Update(GameEngine* game)
{
}

void IntroState::Draw(GameEngine* game)
{
	SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x1A, 0xFF);
	SDL_RenderClear(game->Renderer());

	introTex.render(x, y);

	
	SDL_RenderPresent(game->Renderer());
}

void IntroState::Transition(GameEngine* game)
{
	game->ChangeState(PlayState::Instance());
}