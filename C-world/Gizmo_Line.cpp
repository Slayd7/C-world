#include "Gizmo_Line.h"

void Gizmo_Line::Draw(Vector2D cameraPos, float zoom)
{
    for (std::pair<Vector2D, Vector2D> p : line)
    {
        Vector2D p1 = (p.first * zoom) - cameraPos;
        Vector2D p2 = (p.second * zoom) - cameraPos;
        if ((p1.x < 0 && p2.x < 0) ||
            (p1.y < 0 && p2.y < 0) ||
            (p1.x > SCREEN_WIDTH && p2.x > SCREEN_WIDTH) ||
            (p1.y > SCREEN_HEIGHT && p2.y > SCREEN_HEIGHT))
        {
            continue;
        }

        thickLineRGBA(renderer, p1.x, p1.y, p2.x, p2.y, 2, UI_COLOR_UINT_TO_RGBA(color));
    }
}

void Gizmo_Line::SetLine(Path* p)
{
    Vector2D backPos;
    bool first = true;
    for (Vector2D pos : p->GetNodes())
    {
        if (first) first = false;
        else {
            line.push_back(std::make_pair(pos, backPos));
        }
        backPos = pos;

    }
}
