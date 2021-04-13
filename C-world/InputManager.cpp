#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
	
}

void InputManager::SetCamera(Camera* cam)
{
	activeCam = cam;
}

void InputManager::SetMap(Map* newmap)
{
	activeMap = newmap;
}

int InputManager::HandleEvents(SDL_Event event)
{
	/****************************************************************
	I guess I should establish some "return codes" for this, so it can communicate back
	These are gonna be fairly arbitrary for now

				//// INPUT RETURN CODES ////
				
				1: Game Speed 1x (30 TPS)
				2: Game Speed 2x (60 TPS)
				3: Game Speed 3x (125 TPS)
				4: Game Speed 4x (250 TPS)
				5: Pause Game
				

	*****************************************************************/

	int ret = 0;
	if (!UI::Instance()->HandleEvents(event))
	{
		switch (event.type) {
		case SDL_QUIT:
			ret = -1;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				ret = -1;
				break;
			case SDLK_SPACE:
				ret = 5;
				break;
			case SDLK_1:
				ret = 1;
				break;
			case SDLK_2:
				ret = 2;
				break;
			case SDLK_3:
				ret = 3;
				break;
			case SDLK_4:
				ret = 4;
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
		{
			
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				
				// TEMP PATHFINDING
				if (!firstEntered)
				{
					startPos = activeCam->ScreenToTile(Vector2D(event.motion.x, event.motion.y));

					if (activeMap->GetTileAt(startPos)->IsPassable()) {
						firstEntered = true;

						std::string p = "start: " + std::to_string(startPos.x) + ", " + std::to_string(startPos.y) + "\n";
						printf(p.c_str());
					}
				}
				else
				{
					
					Vector2D goalPos = activeCam->ScreenToTile(Vector2D(event.motion.x, event.motion.y));

					if (activeMap->GetTileAt(goalPos)->IsPassable()) {
						firstEntered = false;
						std::string p = "end: " + std::to_string(goalPos.x) + ", " + std::to_string(goalPos.y) + "\n";
						printf(p.c_str());

						Path* path = new Path(activeMap->Pathfind(startPos, goalPos));

						
						Gizmo_Line* g = new Gizmo_Line(UI::Instance()->renderer);
						g->SetLine(path);
						activeMap->AddGizmo(g);
					}
				}
				// END TEMP

				lmbHeld = true;
				break;
			}
			case SDL_BUTTON_MIDDLE:
				mmbHeld = true;
				break;
			case SDL_BUTTON_RIGHT:
				rmbHeld = true;
				break;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:

			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				lmbHeld = false;
				break;
			case SDL_BUTTON_MIDDLE:
				mmbHeld = false;
				break;
			case SDL_BUTTON_RIGHT:
				rmbHeld = false;
				break;
			}
			break;

		case SDL_MOUSEMOTION:
			if (mmbHeld)
			{
				int x = -event.motion.xrel;
				int y = -event.motion.yrel;
				activeCam->MoveStep(x, y);
			}
			break;
		case SDL_MOUSEWHEEL:
			int x, y;
			SDL_GetMouseState(&x, &y);
			Vector2D p = Vector2D(x, y);
			activeCam->ZoomStep(event.wheel.y, p);

			break;
		}
	}
	else {
		lmbHeld = false;
	}
	return ret;
		
}
