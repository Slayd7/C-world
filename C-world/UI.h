#pragma once
#include "pch.h"
//#include "AssetManager.h"
#include "UIElement.h"
#include "UI_BasicBox.h"
#include "UI_Button.h"
#include "UI_MoveHandle.h"
#include "UI_Text.h"
#include "UI_DynamicNumber.h"
#include "Camera.h"
#include "Defs.h"

class UI
{
public:

	void Init(AssetManager* a, SDL_Renderer* r);
	UIElement* CreateTextBox(std::string str, Vector2D pos);
	void Draw();
	void Update();
	void AddUIElem(UIElement* elem);
	void RemoveUIElem(UIElement* elem);
	bool HandleEvents(SDL_Event event); // Returns true if UI hit
	std::vector<UIElement*> GetUIElements() { return elements; }

	static UI* Instance() {
		if (!_mUI)
			_mUI = new UI();
		return _mUI;
	}
	SDL_Renderer* renderer;

protected:
	std::vector<UIElement*> elements;
	AssetManager* assets;
	UI() {}


private:
	static UI* _mUI;
	int testint = 0;
	UIElement* activeElement;
	void PushToTop(UIElement* elem);

};

