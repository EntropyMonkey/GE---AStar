#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <algorithm>
#include <iostream>
#include <vector>

#include "Node.h"
#include "Link.h"
#include "NPC.h"

class NPC;

class GridNode : public Node<GridNode>
{
public:
	bool					blocked;
	NPC*					npc;

	GridNode(int _x, int _y);

	void					AddLink(GridNode *targetNode, float cost);
	void					AddLink(Link<GridNode> link);
	
	// there can be multiple connections between two nodes. not that i could
	// see any use for that right now
	void					RemoveLink(GridNode *targetNode);

	GridNode *				GetNearestNode(std::vector<GridNode*> &visited);

	void					Block();

	void					Render();

protected:
	int						x;
	int						y;
};

#endif
