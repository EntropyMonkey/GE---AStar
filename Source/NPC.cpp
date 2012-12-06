#include "NPC.h"

NPC::NPC() :
	FSM<NPC>((FSMState<NPC>*)chaseState)
{
	chaseState = new ChaseState(this);
	fleeState = new FleeState(this);

	currentState = chaseState;

	name = "";
}

NPC::~NPC()
{
	delete chaseState;
	delete fleeState;
}

void NPC::CalculateTurnActions()
{
	currentState->Update();
}

void NPC::MoveTo(GridNode *node)
{
	currentNode->npc = NULL;
	currentNode = node;
	currentNode->npc = this;
}

void NPC::Render()
{
	std::cout << name;
}