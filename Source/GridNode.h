#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <algorithm>
#include <iostream>
#include <vector>

#include "Defines.h"
#include "Node.h"
#include "Link.h"
#include "NPC.h"

class NPC;

class GridNode : public Node<GridNode>
{
public:
	struct costCompare
	{
		bool operator() (const GridNode * const one, const GridNode * const two) const
		{
			return one->GetEstimatedCost() < two->GetEstimatedCost();
		}
	};


	bool					blocked;
	bool					inOpenSet;
	bool					inClosedSet;
	bool					current;
	NPC*					npc;

	GridNode(int _x, int _y);

	void					AddLink(GridNode *targetNode, float cost);
	void					AddLink(Link<GridNode> link);
	
	// there can be multiple connections between two nodes. not that i could
	// see any use for that right now
	void					RemoveLink(GridNode *targetNode);

	std::vector<Link<GridNode> > GetConnections();

	GridNode *				GetNearestNode(std::vector<GridNode*> &visited);

	void					Block();

	void					Render();

	inline int				GetCoordX() const { return x; }
	inline int				GetCoordY() const { return y; }

	inline float			GetCost() const { return pathCost; }
	inline void				SetCost(float cost) { pathCost = cost; }

	inline float			GetEstimatedCost() const { return eCost; }
	inline void				SetEstimatedCost(float cost) { eCost = cost; }

protected:
	int						x;
	int						y;

	float					pathCost;
	float					eCost; // estimated cost to target
};

#endif
