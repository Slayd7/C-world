#pragma once
#include "Entity.h"
#include "Path.h"
#include "SteeringBehavior.h"
#include "Gizmo_Line.h"

class Actor : virtual public Entity
{
public:
	Actor();
	~Actor();
	virtual void Tick();
	virtual void Draw(Vector2D camPos, double zoom);

	void SetPath(Path* p);

	float getMaxVelocity() { return max_velocity; }
	Vector2D getVelocity() { return velocity; }
	float getMaxForce() { return max_force; }


private:
	
	Gizmo_Line* line;

	float orientation;
	float max_force;
	float max_velocity;

	Vector2D velocity;
	Vector2D target;

	Path* path;

	/// <summary>
	/// This function will check to see if the actor's currently occupied tile has changed,
	/// and if it HAS changed, register itself in its new tile and remove itself from the old tile.
	/// Returns true if valid tile change,
	/// </summary>
	/// <returns>True if valid tile change was completed,
	/// false if tile change is illegal for any reason
	/// (tile unpassable, already occupied, etc)</returns>
	bool CheckValidMove(Vector2D pos);

};
