#ifndef GRID_H
#define GRID_H

#include <Windows.h>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Graph.h"
#include "GridNode.h"

class Grid : public Graph<GridNode>
{
public:
	Grid();

	void					Create(int width, int height);

	virtual void			AddNode(int x, int y);

	virtual bool			Update();

protected:
	unsigned int			width;
	unsigned int			height;

	NPC						alpha;
	NPC						omega;

	void					DrawToConsole();
};

#endif
