#pragma once
#include "UIElement.h"
#include <regex>

class UI_Text :
	public UIElement
{
public:
	~UI_Text();
	static UI_Text* Parse(AssetManager* a, SDL_Renderer* r, std::string str, int size, int w, int h);

	void ChangeText(std::string str);

	virtual void Draw() override;
	virtual bool HandleEvents(SDL_Event event) override;
	virtual int GetHeight() override;
	virtual int GetWidth() override;	

private:	
	UI_Text(std::string str, TEXTFLAGS flags, TTF_Font* font);
	UI_Text* nextLine; // Next VERTICAL line.
					   // Horizontal neighbors are in children
	LTexture tex;
	void AddLine(UI_Text* next);
};

