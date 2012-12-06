#ifndef NPC_H
#define NPC_H

#include <iostream>

#include "FSM.h"

#include "ChaseState.h"
#include "FleeState.h"

#include "GridNode.h"

class ChaseState;
class FleeState;

class GridNode;

class NPC : public FSM<NPC>
{
public:
	GridNode*				currentNode;
	GridNode*				targetNode;

	ChaseState*				chaseState;
	FleeState*				fleeState;

	char*					name;

	NPC();
	~NPC();

	void					CalculateTurnActions();
	void					MoveTo(GridNode *node);
	void					Render();

protected:
};

#endif
