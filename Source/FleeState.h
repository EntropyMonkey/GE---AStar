#ifndef FLEESTATE_H
#define FLEESTATE_H

#include "FSMState.h"
#include "NPC.h"

class NPC;

class FleeState : public FSMState<NPC>
{
public:
	FleeState(NPC *owner);

	void Enter();
	void Update();
	void Exit();

protected:
};

#endif
