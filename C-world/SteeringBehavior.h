#pragma once
#include "Actor.h"
#include <vector>

class Actor;
class SteeringBehavior
{
public:

	/* Add here your own Steering Behavior functions declarations */
	static Vector2D Seek(Actor* agent, Vector2D target);
	static Vector2D Flee(Actor* agent, Vector2D target);
	static Vector2D Arrive(Actor* agent, Vector2D target, float r);
	static Vector2D Pursue(Actor* agent, Vector2D target, float maxSpeed);
	static Vector2D Evade(Actor* agent, Vector2D target, float maxSpeed);
	static Vector2D Wander(Actor* agent, Vector2D target);
	static Vector2D CollisionAvoidance(Actor* agent, Vector2D target, std::vector <Vector2D> obstacles, float MAX_AHEAD, float MAX_AVOID_FORCE);
	static Vector2D Combining(Actor* agent, Vector2D target);



};
