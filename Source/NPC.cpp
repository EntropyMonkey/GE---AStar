#include "NPC.h"

NPC::NPC(GridNode *startNode, char _name = ' ') :
	FSM<NPC>((FSMState<NPC>*)chaseState),
	currentNode(startNode),
	name(_name)
{
	currentNode->npc = this;

	chaseState = new ChaseState(this);
	fleeState = new FleeState(this);

	currentState = chaseState;

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