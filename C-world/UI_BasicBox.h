#pragma once
#include "UIElement.h"

class UI_BasicBox : public UIElement
{
public:
	UI_BasicBox() {};
	UI_BasicBox(AssetManager* a, SDL_Renderer* r);
	~UI_BasicBox();
	void SetRelativePosition(Vector2D newpos);
	void Draw();
	void AddChild(UIElement* newChild, UI_LAYOUT side, UI_LAYOUT align);

protected:
	std::string contents;
	bool centered = false;

	virtual bool HandleEvents(SDL_Event event) override;
	Vector2D offset = Vector2D(0, 0);
	void Resize();
};

