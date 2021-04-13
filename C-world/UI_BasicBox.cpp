#include "pch.h"
#include "UI_BasicBox.h"

void UI_BasicBox::AddChild(UIElement* newChild, UI_LAYOUT side, UI_LAYOUT align)
{
	UIElement::AddChild(newChild);
	Vector2D curPos = newChild->GetRelativePosition();
	switch (side) {
	default:
	case UI_LAYOUT::BOTTOM:
		newChild->SetRelativePosition(Vector2D(curPos.x, h + (UI_BORDEROFFSET*5)));
		break;
	case UI_LAYOUT::TOP:
		newChild->SetRelativePosition(Vector2D(curPos.x, -newChild->GetHeight() - UI_BORDEROFFSET));
		break;
	case UI_LAYOUT::LEFT:
		break;
	case UI_LAYOUT::RIGHT:
		break;
	}

	Resize();
	curPos = newChild->GetRelativePosition();
	switch (align) {
	default:
	case UI_LAYOUT::ALIGN_LEFT:
		newChild->SetRelativePosition(Vector2D(UI_BORDEROFFSET, curPos.y));
		break;
	case UI_LAYOUT::ALIGN_RIGHT:
		newChild->SetRelativePosition(Vector2D(w - newChild->GetWidth() - UI_BORDEROFFSET, curPos.y));
		break;
	case UI_LAYOUT::CENTERED:
		newChild->CenterOn(Vector2D(w * 0.5, curPos.y));
		break;
	}
}

void UI_BasicBox::Draw() {
	
	Vector2D drawPos = GetAbsolutePosition();
	
	// Fill
	SDL_SetRenderDrawColor(renderer, 
		UI_COLOR_UINT_TO_RGBA(fillColor));
	SDL_Rect rect = { drawPos.x + offset.x, drawPos.y + offset.y , GetWidth(), GetHeight() };
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	
	// Border
	thickLineRGBA(renderer, drawPos.x, drawPos.y, drawPos.x + w, drawPos.y, 2, 
		UI_COLOR_UINT_TO_RGBA(borderColor));
	thickLineRGBA(renderer, drawPos.x, drawPos.y + h, drawPos.x + w, drawPos.y + h, 2, 
		UI_COLOR_UINT_TO_RGBA(borderColor));
	thickLineRGBA(renderer, drawPos.x, drawPos.y, drawPos.x, drawPos.y + h, 2,
		UI_COLOR_UINT_TO_RGBA(borderColor));
	thickLineRGBA(renderer, drawPos.x + w, drawPos.y, drawPos.x + w, drawPos.y + h, 2,
		UI_COLOR_UINT_TO_RGBA(borderColor));
	
	UIElement::Draw();
}

bool UI_BasicBox::HandleEvents(SDL_Event event)
{
	bool ret = (event.type == SDL_MOUSEBUTTONDOWN) && InBounds(Vector2D(event.motion.x, event.motion.y));
	for (UIElement* child : children) {
		if (children.size() > 0) {
			ret = ret | child->HandleEvents(event);
		}
	}
	return ret;
}

UI_BasicBox::UI_BasicBox(AssetManager* a, SDL_Renderer* r) {
	
	pos = Vector2D(0, 0);
	renderer = r;
	
	enabled = true;
}

UI_BasicBox::~UI_BasicBox()
{
	UIElement::~UIElement();
}

void UI_BasicBox::SetRelativePosition(Vector2D newpos) {
	pos = newpos; 
}

void UI_BasicBox::Resize() {
	int maxX = 0, maxY = 0;
	int minX = 0, minY = 0;
	for (UIElement* child : children) {
		Vector2D p = child->GetRelativePosition();
		int width = child->GetWidth();
		int height = child->GetHeight();
		if (maxX < p.x + width)
			maxX = p.x + width;
		if (maxY < p.y + height)
			maxY = p.y + height ;
		if (minX > p.x)
			minX = p.x - (UI_BORDEROFFSET * 2);
		if (minY > p.y)
			minY = p.y - UI_BORDEROFFSET;
	}
	w = maxX - minX + (UI_BORDEROFFSET * 2);
	h = maxY - minY + UI_BORDEROFFSET;
	for (UIElement* child : children) {
		child->Move(Vector2D(-minX, -minY));
	}
}