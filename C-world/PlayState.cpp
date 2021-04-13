#include "pch.h"
#include "PlayState.h"

PlayState* PlayState::_mPlayState;
LTexture* campos = NULL;

void PlayState::Init()
{
	renderer = GameEngine::Renderer();
	
	activeMap = new RegularMap();
	if (!activeMap->Generate(-1, GameEngine::Assets())) {
		printf("Map generation failed!");
	}

	for (int i = 0; i < 500; i++)
	{


		Actor* e = new Actor();
		LTexture* tex = GameEngine::Assets()->getTexture(GameEngine::Assets()->getTextureId("lemmy"));
		e->SetName("Lemmy" + std::to_string(i));
		e->setTexture(tex);
		e->SetMap(activeMap);

		activeMap->Entities()->AddEntity(e);


		Vector2D origin(rand() % 200, rand() % 200);
		while (!activeMap->GetTileAt(origin)->IsPassable())
		{
			printf("Origin not passable!\n");
			origin = Vector2D(rand() % 200, rand() % 200);
		}
		e->SetTilePosition(origin);

		Vector2D dest(rand() % 200, rand() % 200);
		while (!activeMap->GetTileAt(dest)->IsPassable())
		{
			printf("Destination not passable!\n");
			dest = Vector2D(rand() % 200, rand() % 200);
		}

		Path* p = new Path();
		e->SetPath(p);

		//Path* p = new Path(activeMap->Pathfind(origin, dest));

		//e->SetPath(p);
	}

	/*Gizmo_Line* g = new Gizmo_Line(renderer);
	g->SetLine(p);
	g->SetColor(0x00FFFF88);
	activeMap->AddGizmo(g);
	*/

	activeCam = new Camera();

	input = new InputManager();
	input->SetCamera(activeCam);
	input->SetMap(activeMap);

	campos = GameEngine::Assets()->newTextTexture
		(std::string("Camera: %s - %s", 0, 0), "rust_never_sleeps", 1, SDL_Color{ 0, 0, 0, 255 });
	
	UI::Instance()->Init(GameEngine::Assets(), renderer);
	//UI::Instance()->CreateTextBox("Test {s}string{/s} but you {b}never expected{/b} it to be this long oh dang is this inserted text i'm seeing string framework i build hoopefully this will show up on miultiple lines and i don't need to go back and fix some stupid shit athat didn't work like i was hoping it would i wonder if this is long enough yetTest string but you never expected it to be this long oh my god it just keeps going in order to test ou the string framework i build hoopefully this will show up on miultiple lines and i don't need to go back and fix some stupid shit athat didn't work like i was hoping it would i wonder if this is long enough yetTest string but you never expected it to be this long oh my god it just keeps going in order to test ou the string framework i build hoopefully this will show up on miultiple lines and i don't need to go back and fix some stupid shit athat didn't work like i was hoping it would i wonder if this is long enough yetTest string but you never expected it to be this long oh my god it just keeps going in order to test ou the string framework i build hoopefully this will show up on miultiple lines and i don't need to go back and fix some stupid shit athat didn't work like i was hoping it would i wonder if this is long enough yetTest string but you never expected it to be this long oh my god it just keeps going in order to test ou the string framework i build hoopefully this will show up on miultiple lines and i don't need to go back and fix some stupid shit athat didn't work like i was hoping it would i wonder if this is long enough yetTest string but you never expected it to be this long oh my god it just keeps going in order to test ou the string framework i build hoopefully this will show up on miultiple lines and i don't need to go back and fix some stupid shit athat didn't work like i was hoping it would i wonder if this is long enough yetTest string but you never expected it to be this long oh my god it just keeps going in order to test ou the string framework i build hoopefully this will show up on miultiple lines and i don't need to go back and fix some stupid shit athat didn't work like i was hoping it would i wonder if this is long enough yetTest string but you never expected it to be this long oh my god it just keeps going in order to test ou the string framework i build hoopefully this will show up on miultiple lines and i don't need to go back and fix some stupid shit athat didn't work like i was hoping it would i wonder if this is long enough yet", Position(SCREEN_WIDTH / 2, 100));
	//UI::Instance()->CreateTextBox("Testing! Hopefully we're feeling much happier now. What is that I hear? Is it a {h}HIGHLIGHTED PHRASE???{/h} What about... a {b}BOLD{/b} word. Or maybe, an {i}ITALICIZED{/i} word? Maybe... {b}{i}both?{/b}{/i} Okay, okay. Let's talk {h}C{/h}{s}O{/s}L{h}O{/h}{s}R{/s}S! What about... {b}{i}{s}BOLD ITA{/s}{h}LIC COLORS!{/h}{/i}{/b}", Position(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	
	timer = GameEngine::Timer();
	timer->start();
}

void PlayState::Cleanup() 
{
}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
	
}

void PlayState::HandleEvents(GameEngine* game)
{
	SDL_Event event;

	while(SDL_PollEvent(&event) != 0) {
		switch (input->HandleEvents(event))
		{
		case -1:	// Quit Game
			GameEngine::Instance()->Quit();
			break;

		
		case 1:
			gameSpeed = 0;
			break;
		case 2:
			gameSpeed = 1;
			break;
		case 3:
			gameSpeed = 2;
			break;
		case 4:
			gameSpeed = 3;
			break;
		case 5:		// Pause Game
			if (timer->isPaused()) timer->unpause();
			else timer->pause();
			break;
		}
	}
}

void PlayState::Update(GameEngine* game)
{
	
	if (timer->getTicks() >= (lastTick + TICKDURATION[gameSpeed]))
	{
		tick++;
		activeMap->Entities()->Tick();
		lastTick = timer->getTicks();
	}

	UI::Instance()->Update();

}

void PlayState::Draw(GameEngine* game)
{
	SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x1A, 0xFF);
	SDL_RenderClear(renderer);
		
	if (activeCam != NULL && activeMap != NULL) {
		activeCam->Draw(activeMap);
	}
	
	Vector2D pos = activeCam->GetCameraPosition();
	Vector2D tPos = activeCam->GridToTile(pos);
	std::string str = "Camera: [" + std::to_string((int)pos.x) + ", ";
	str += std::to_string((int)pos.y) + "]";
	str += " [" + std::to_string((int)tPos.x) + ", " + std::to_string((int)tPos.y) + "]   ";

	std::string s = std::to_string(timer->getTicks() / 1000.0);
	s = s.substr(0, s.length() - 3);
	str += " Time: " + s; 
	str += "    Ticks: " + std::to_string(tick);
	str += "    Speed: " + std::to_string(TICKSPERSECOND[gameSpeed]) + " TPS";

	campos = GameEngine::Assets()->newTextTexture(str, "basic", 2, SDL_Color{ 255, 255, 255, 255 });
	campos->render(15, 15);
	UI::Instance()->Draw();

	SDL_RenderPresent(renderer);
	campos->Cleanup();
}
