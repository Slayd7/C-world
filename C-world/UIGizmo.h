#pragma once
#include "pch.h"
#include "Defs.h"
#include "LTexture.h"
//#include "GameEngine.h"

class UIGizmo
{
public:
    UIGizmo(SDL_Renderer* r)
    {
        enabled = true;
        renderer = r;
    }
    virtual void Draw(Vector2D cameraPos, float zoom) = 0;
    void Enable() { enabled = true; }
    void Disable() { enabled = false; }
    bool IsEnabled() { return enabled; }

protected:
    UIGizmo() {}
    bool enabled;
    Vector2D pos;
    SDL_Renderer* renderer;
};

