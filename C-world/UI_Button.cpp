#include "pch.h"
#include "UI_Button.h"

UI_Button::UI_Button(AssetManager* a, SDL_Renderer* r, std::string str, std::function<void()> onPress)
{
	assets = a;
	renderer = r;
	UI_Text* txt = UI_Text::Parse(a, r, str, 1, 100, 100);
	this->AddChild(txt, UI_LAYOUT::TOP, UI_LAYOUT::CENTERED);
	
	OnPress = onPress;
	h = txt->GetHeight() + (2 * UI_BORDEROFFSET);
	w = txt->GetWidth() + (2 * UI_BORDEROFFSET);

	borderColor = UI_BUTTONBORDERCOLOR;
	fillColor = UI_BUTTONFILLINACTIVE;

	enabled = true;
}

bool UI_Button::HandleEvents(SDL_Event event)
{
	bool ret = false;
	switch (event.type) {
	case SDL_MOUSEMOTION:
		if (InBounds(Vector2D(event.motion.x, event.motion.y)))
		{
			highlighted = true;
			if (!pressed)
				fillColor = UI_BUTTONFILLACTIVE;
		}
		else if (highlighted) {
			fillColor = UI_BUTTONFILLINACTIVE;
			highlighted = false;
			pressed = false;
			offset = Vector2D(0, 0);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (InBounds(Vector2D(event.motion.x, event.motion.y)))
		{
			pressed = true;
			fillColor = UI_BUTTONPRESSED;
			offset = Vector2D(2, 2);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (InBounds(Vector2D(event.motion.x, event.motion.y)))
		{
			if (pressed)
			{
				if (OnPress != NULL)
					OnPress();
				ret = true;
				pressed = false;
				fillColor = UI_BUTTONFILLACTIVE;
				offset = Vector2D(0, 0);
			}
		}
		break;
	}
	return ret;
	
}
