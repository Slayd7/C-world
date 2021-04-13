#include "pch.h"
#include "UIElement.h"

void UIElement::AddChild(UIElement* newChild)
{
	children.push_back(newChild);
	newChild->SetParent(this);
}

Vector2D UIElement::GetAbsolutePosition()
{
	if (parent == NULL) return pos;
	return parent->GetAbsolutePosition() + pos;
}

void UIElement::SetAbsolutePosition(Vector2D newpos)
{
	if (parent == NULL) pos = newpos;
	else {
		pos = newpos - parent->GetAbsolutePosition();
	}
}

void UIElement::CenterOn(Vector2D centerpos) {
	pos = centerpos - Vector2D(w * 0.5, 0);
}

bool UIElement::InBounds(Vector2D p)
{
	Vector2D p2 = GetAbsolutePosition();

	return (p.x > p2.x &&
			p.x < p2.x + w &&
			p.y > p2.y &&
			p.y < p2.y + h);
}

bool UIElement::IsActive() {
	bool ret = enabled;
	for (UIElement* child : children)
	{
		ret = ret | child->IsActive();
	}
	return ret;
}