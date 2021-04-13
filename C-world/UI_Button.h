#pragma once
#include "UI_BasicBox.h"
#include "UI_Text.h"

class UI_Button : public UI_BasicBox
{
public:
	UI_Button(AssetManager* a, SDL_Renderer* r, std::string str, std::function<void()> onPress);
	virtual bool HandleEvents(SDL_Event event) override;

protected:
	bool highlighted, pressed;	
	std::function<void()> OnPress;
};

