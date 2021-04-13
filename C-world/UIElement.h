#pragma once
#include "pch.h"
#include "Defs.h"
#include "AssetManager.h"
#include "LTexture.h"
#include <functional>

class UIElement
{
public:
	~UIElement() { for (UIElement* child : children) { child->~UIElement(); } }

	virtual void Draw() {
		for (UIElement* child : children) child->Draw();
	}
	virtual bool HandleEvents(SDL_Event event) = 0;
	virtual void Update() {
		for (UIElement* child : children) child->Update();
	};

	virtual bool IsActive();

	void Enable() { enabled = true; }
	void Disable() { enabled = false; }
	bool IsEnabled() { return enabled; }

	virtual void AddChild(UIElement* newChild);
	std::vector<UIElement*> GetChildren() { return children; }
	void SetParent(UIElement* p) { parent = p; }

	Vector2D GetRelativePosition() { return pos; }
	Vector2D GetAbsolutePosition();
	void SetRelativePosition(Vector2D newpos) { pos = newpos; }
	void SetAbsolutePosition(Vector2D newpos);
	void Move(Vector2D newpos) {
		pos = pos + newpos;
	}

	void CenterOn(Vector2D centerpos);

	void SetWidth(int width) { w = width; }
	void SetHeight(int height) { h = height; }
	virtual int GetHeight() { return h; }
	virtual int GetWidth() { return w; }

	bool InBounds(Vector2D p);

protected:
	Vector2D pos;
	int w, h;
	bool enabled, active;

	AssetManager* assets;
	UIElement* parent;
	std::vector<UIElement*> children;
	SDL_Renderer* renderer;

	Uint32 borderColor = UI_BORDERCOLOR,
		fillColor = UI_FILLCOLOR,
		inactiveColor = UI_BUTTONFILLINACTIVE,
		activeColor = UI_BUTTONFILLACTIVE,
		highlightColor = UI_BUTTONFILLACTIVE,
		textPrimaryColor = UI_TEXTPRIMARYCOLOR,
		textSecondaryColor = UI_TEXTSECONDARYCOLOR,
		textHighlightColor = UI_TEXTHIGHLIGHTCOLOR;
};

