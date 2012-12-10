#ifndef NPC_H
#define NPC_H

#include <iostream>

#include "FSM.h"

#include "ChaseState.h"
#include "FleeState.h"

#include "Grid.h"
#include "GridNode.h"

class ChaseState;
class FleeState;

class Grid;
class GridNode;

class NPC : public FSM<NPC>
{
public:
	Grid*					grid;
	NPC*					enemy;
	GridNode*				currentNode;

	ChaseState*				chaseState;
	FleeState*				fleeState;

	char					name;

	NPC(GridNode *startNode, char _name);
	~NPC();

	void					CalculateTurnActions();
	void					MoveTo(GridNode *node);
	void					Render();

};

#endif
