#include "pch.h"
#include "Actor.h"


int ticks = 0;

Actor::Actor() : velocity(Vector2D(0,0)),
                 max_velocity(10),
                 max_force(10)
{
   // line = new Gizmo_Line()
}

Actor::~Actor()
{
}

void Actor::Tick()
{
    Vector2D steering_force;
    if (target != NULL)
    {
        if (Vector2D::Distance(position, target) < max_velocity)
        {
            position = target;
            target = NULL;
            velocity = Vector2D(0, 0);
        }
        else {
            steering_force = SteeringBehavior::Arrive(this, target, Vector2D::Distance(position, target));
        }
    }
    if (path != NULL)
    {
        if (target == NULL)
        {
            if (path->Size() > 0)
            {
                target = *path->PopNode()
                    - Vector2D((clip->w * 0.5), (clip->h * 0.5));
                // Offset the target by half the clip size, to center the actor
            }
            else {
                path = NULL;
                // TEMP FOR TESTING MOVEMENT

                std::string s = name + " searching for new target...\n";
                Vector2D newDest = Vector2D(rand() % MAXMAPSIZEX, rand() % MAXMAPSIZEY);
                while (!currentMap->GetTileAt(newDest)->IsPassable())
                {
                    s += "Impassable destination found, trying again...\n";
                    newDest = Vector2D(rand() % MAXMAPSIZEX, rand() % MAXMAPSIZEY);
                }
                s += "New destination found! Coords: [" + newDest.toString() + "]\n\n";
                printf(s.c_str());
                path = new Path(currentMap->Pathfind(GetTilePosition(), newDest));


                target = *path->PopNode()
                    - Vector2D((clip->w * 0.5), (clip->h * 0.5));

                // END TEMP
            }
        }
    }
    else {
        steering_force = SteeringBehavior::Wander(this, this->GetScreenPosition());
    }

    // Adding mass to this just seems to complicate things, so we're just gonna treat everything as massless
    //Vector2D acceleration = steering_force / mass;
    velocity = velocity + steering_force;
    velocity = velocity.Truncate(max_velocity);

    //std::string s = "Force: " + steering_force.toString() + "\n";
    //s += "Accel: " + acceleration.toString() + "\n";
    //s += "Veloc: " + velocity.toString() + "\n";
    //s += "\n";

    //printf(s.c_str());

    Vector2D nextPosition = position + velocity;

    if (CheckValidMove(nextPosition))
    {
        position = nextPosition;
    }

    ticks++;

}

void Actor::SetPath(Path* p)
{
    if (path)
    {
        path->~Path();
        path = NULL;
    }
    path = p;
}

void Actor::Draw(Vector2D camPos, double zoom)
{
    //if (path != NULL) {
    //    line->Draw(camPos, zoom);
    //}
    Vector2D p = (position * zoom) - camPos;
    if ((p.x < -(clip->w*zoom)) ||
        (p.y < -(clip->h*zoom)) ||
        (p.x > SCREEN_WIDTH) ||
        (p.y > SCREEN_HEIGHT))
    {
        return;
    }
	texture->render(p.x, p.y, zoom, clip);
}

bool Actor::CheckValidMove(Vector2D pos)
{
    Vector2D centeredPos(pos.x + (clip->w * 0.5), pos.y + (clip->h * 0.5));
    if (occupiedTile == NULL)
    {
        occupiedTile = currentMap->GetTileAt(
            Vector2D(position.x + (clip->w * 0.5), position.y + (clip->h * 0.5)) * TILERATIO);
    }
    Vector2D tasfdasdf = centeredPos * TILERATIO;

    if ((int)(centeredPos.x * TILERATIO) != occupiedTile->getX() ||
        (int)(centeredPos.y * TILERATIO) != occupiedTile->getY()) 
    {
        Tile* t = currentMap->GetTileAt(centeredPos * TILERATIO);
        if (t->IsPassable())
        {
            occupiedTile->RemoveEntity(this);
            t->AddEntity(this, true);
            occupiedTile = t;
            return true;
        }
        return false;
    }
    return true;
}