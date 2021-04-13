#include "pch.h"
#include "UI_MoveHandle.h"

void UI_MoveHandle::Draw()
{
	Vector2D drawPos = GetAbsolutePosition();
	for (int i = 0; i < tickAmount; i++) {
		thickLineRGBA(
			renderer,
			drawPos.x + (i * tickSpacing),
			drawPos.y,
			drawPos.x + (i * tickSpacing),
			drawPos.y + tickLength,
			tickWidth,
			UI_COLOR_UINT_TO_RGBA(borderColor)
		);
	}
	UIElement::Draw();
}

UI_MoveHandle::UI_MoveHandle(SDL_Renderer* r)
{ 
	renderer = r;
	h = tickLength;
	w = ((tickSpacing) * tickAmount) - tickSpacing; 
}

bool UI_MoveHandle::IsActive() {
	return pressed;
}

bool UI_MoveHandle::HandleEvents(SDL_Event event)
{
	if (InBounds(Vector2D(event.motion.x, event.motion.y)) || pressed)
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			pressed = true;
			break;
		case SDL_MOUSEBUTTONUP:
			pressed = false;
			break;
		case SDL_MOUSEMOTION:
			if (pressed)
				parent->Move(Vector2D(event.motion.xrel, event.motion.yrel));
			break;
		}
	}
	return pressed;
}
