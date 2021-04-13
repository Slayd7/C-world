#pragma once
#include "UIGizmo.h"
#include "Path.h"
#include <vector>

class Gizmo_Line : public UIGizmo
{
public:
    virtual void Draw(Vector2D cameraPos, float zoom) override;

    Gizmo_Line(SDL_Renderer* r) {
        enabled = true;
        //if (r == NULL) r = GameEngine::Renderer();
        renderer = r;
    }

    void SetLine(std::vector<std::pair<Vector2D, Vector2D>> newLine)
    {
        line = newLine;
    }

    void SetLine(Path* p);
   

    void SetColor(Uint32 newColor) { color = newColor; }

private:
    std::vector<std::pair<Vector2D, Vector2D>> line;
    Uint32 color = UI_GIZMOCOLOR;
};

