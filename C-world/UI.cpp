#include "pch.h"
#include "UI.h"
#include <algorithm>

UI* UI::_mUI;

void UI::Init(AssetManager* a, SDL_Renderer* r)
{
	assets = a;
	renderer = r;
}

UIElement* UI::CreateTextBox(std::string str, Vector2D pos)
{
	UI_BasicBox* box = new UI_BasicBox(assets, renderer);
	UI_Text* txt = UI_Text::Parse(assets, renderer, str, 1, 600, 1080); 
	UI_Button* button = new UI_Button(assets, renderer, "Close", [box, this] 
		{
			RemoveUIElem(box);
			box->~UI_BasicBox(); 
		});
	UI_MoveHandle* handle = new UI_MoveHandle(renderer);


	//UI_DynamicNumber* dyn = new UI_DynamicNumber(&testint, 1, assets);

	box->AddChild(txt, UI_LAYOUT::TOP, UI_LAYOUT::ALIGN_LEFT);
	box->AddChild(handle, UI_LAYOUT::TOP, UI_LAYOUT::CENTERED);
	box->AddChild(button, UI_LAYOUT::BOTTOM, UI_LAYOUT::CENTERED);
	//box->AddChild(dyn, UI_LAYOUT::BOTTOM, UI_LAYOUT::CENTERED);

	AddUIElem(box);
	box->CenterOn(pos);
	return box;
}

void UI::Draw() {
	for (UIElement* e : elements)
	{
		if (e->IsEnabled())
		{
			e->Draw();
		}
	}
}

void UI::Update()
{
	for (UIElement* e : elements)
	{
		if (e->IsEnabled())
			e->Update();
	}
}

bool UI::HandleEvents(SDL_Event event)
{
	testint++;
	bool ret = false;
	UIElement* toPush = NULL;
	
	switch (event.type) {

	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEMOTION:
		
		for (std::vector<UIElement*>::reverse_iterator e = elements.rbegin();
			 e != elements.rend(); 
			 e++) {
			UIElement* e2 = *e;
			if (e2->IsEnabled() && (e2->IsActive() || e2->InBounds(Vector2D(event.motion.x, event.motion.y))))
			{  
				if (e2->HandleEvents(event))
				{
					toPush = e2;
					ret = true; 
					break;
				}
			}
		}
		break;
	case SDL_MOUSEWHEEL:
		int x, y;
		SDL_GetMouseState(&x, &y);

		break;
	}
	if (toPush != NULL && toPush->IsEnabled())
		PushToTop(toPush);
	return ret;
}

void UI::AddUIElem(UIElement* elem) {
	elements.push_back(elem);
}

void UI::RemoveUIElem(UIElement* elem) {
	elements.erase(std::remove(elements.begin(), elements.end(), elem), elements.end());	
}

void UI::PushToTop(UIElement* elem)
{
	std::vector<UIElement*>::iterator pos = std::find(elements.begin(), elements.end(), elem);
	if (pos != elements.end()) {
		std::rotate(pos, pos + 1, elements.end());
	}
}