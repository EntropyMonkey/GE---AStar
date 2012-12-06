#ifndef CHASESTATE_H
#define CHASESTATE_H

#include <vector>

#include "FSMState.h"
#include "NPC.h"
#include "GridNode.h"

class NPC;
class GridNode;

class ChaseState : public FSMState<NPC>
{
public:
	ChaseState(NPC *_owner);

	void						Enter();
	void						Update();
	void						Exit();

protected:
	std::vector<GridNode*>		visited;
};

#endif
