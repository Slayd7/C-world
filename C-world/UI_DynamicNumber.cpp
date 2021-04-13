#include "UI_DynamicNumber.h"

void UI_DynamicNumber::Update()
{
    int n = *num;
    if (n != prevnum)
    {
        textTextures.clear();
        while (n != 0)
        {
            textTextures.push_back(assets->GetNumberFromPool(n % 10, size));
            n = n * 0.1;
        }
        if (textTextures.size() == 0)
        {
            textTextures.push_back(assets->GetNumberFromPool(0, size));
        }
    }

    prevnum = *num;
    UIElement::Update();
}

void UI_DynamicNumber::Draw()
{
    int w = 0;
    for (std::vector<LTexture*>::reverse_iterator i = textTextures.rbegin();
        i != textTextures.rend(); ++i)
    {
        LTexture* t = *i;
        Vector2D p = GetAbsolutePosition();
        t->render(p.x + w, p.y);
        w += t->getWidth();        
    }
    UIElement::Draw();
}
