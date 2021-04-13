#pragma once
#include "UIElement.h"
class UI_DynamicNumber : public UIElement
{
public:
    UI_DynamicNumber(int* num, int size, AssetManager* a)
    {
        this->num = num;
        assets = a;
        this->size = size;
        prevnum = 0;
    }
    
private:
    AssetManager* assets;
    int* num;
    int prevnum;
    int size;
    void Update() override;
    void Draw() override;
    bool HandleEvents(SDL_Event event) override { return false; }

    std::vector<LTexture*> textTextures;
};

