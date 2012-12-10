#ifndef GRID_H
#define GRID_H

#include <Windows.h>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <iostream>

#include "Defines.h"
#include "Graph.h"
#include "GridNode.h"

class Grid : public Graph<GridNode>
{
public:
	Grid();
	~Grid();

	void					Reset();
	void					Create(int width, int height);

	virtual void			AddNode(unsigned int x, unsigned int y);
	GridNode*				GetNode(unsigned int x, unsigned int y);
	GridNode*				GetFreeNode();

	virtual bool			Update();

	GridNode*				FindPathAStar(GridNode *start, GridNode *target);

	void					Flush();
	float					GetDistance(GridNode *one, GridNode *two);

protected:
	unsigned int			width;
	unsigned int			height;

	NPC						*alpha;
	NPC						*omega;

	void					DrawToConsole();
	
	void					PrintPath(std::map<GridNode*,GridNode*> &parentChain, 
		GridNode* parent);

	void					GetPath(std::map<GridNode*, GridNode*> &parentChain, 
		GridNode *parent, std::list<GridNode*> &path);
};

#endif
