#pragma once
#include "UIElement.h"
class UI_MoveHandle :
	public UIElement
{
public:
	UI_MoveHandle(SDL_Renderer* r);
	~UI_MoveHandle() {}
	virtual void Draw() override;
	virtual bool HandleEvents(SDL_Event event) override;
	virtual bool IsActive() override;
private:
	int tickLength = 15;
	int tickSpacing = 5;
	int tickAmount = 30;
	int tickWidth = 2;

	bool pressed;
};

