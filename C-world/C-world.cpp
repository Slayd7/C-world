#include "pch.h"
#include "C-world.h"

int main(int argc, char* args[])
{
	GameEngine* game = GameEngine::Instance();

	if (game->Init("C-World", 1920, 1080, 0, false))
	{
		//game->ChangeState(IntroState::Instance());
		game->ChangeState(PlayState::Instance());

		while (game->Running())
		{
			game->HandleEvents();
			game->Update();
			game->Draw();
		}

		game->Cleanup();
	}
	return 0;
}