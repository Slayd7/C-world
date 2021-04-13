#pragma once
#include "pch.h"
#include <vector>
#include "Defs.h"
#include "Tile.h"

class Path
{
public:
	Path() { }
	Path(std::vector<Tile*> tilepath);
	~Path() { }
	void AddNode(Vector2D node) { nodes.push_back(node); };
	Vector2D* PopNode();
	double Size() { return nodes.size(); }

	std::vector<Vector2D> GetNodes() { return nodes; };

private:

	std::vector<Vector2D> nodes;
};

