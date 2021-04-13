#include "Path.h"

Path::Path(std::vector<Tile*> tilepath)
{
	int angle = 0, prevangle = 0;
	Vector2D prev;
	bool first = true;
	for (Tile* t : tilepath)
	{
		Vector2D p = t->GetPos();
		if (first)
		{
			first = false;
		}
		else
		{
			// Find angle of path, if angle ever changes then add a node
			// y = mx
			// m = y/x
			if (prev.x != p.x) {
				angle = (prev.y - p.y) / (prev.x - p.x);
			}
			else angle = 2; // in this case, y/x = div by 0, so just set to 2

		}
		if (angle != prevangle)
		{
			nodes.push_back(prev * TILESIZE + (TILESIZE * 0.5));
		}

		prevangle = angle;
		prev = p;
		
		
	}
	nodes.push_back(prev * TILESIZE + (TILESIZE * 0.5));
}

Vector2D* Path::PopNode() {
	Vector2D p = nodes.at(0);
	nodes.erase(nodes.begin());
	return &p;
}