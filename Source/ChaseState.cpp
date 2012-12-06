#include "ChaseState.h"

ChaseState::ChaseState(NPC *_owner) :
	FSMState<NPC>(_owner)
{

}

void ChaseState::Enter()
{
	visited.push_back(owner->currentNode);
}

void ChaseState::Update()
{
	GridNode *newNode = owner->currentNode->GetNearestNode(visited);

	if (newNode != NULL)
	{
		owner->MoveTo(newNode);
		visited.push_back(owner->currentNode);
	}
	else
	{
		visited.clear();
	}
}

void ChaseState::Exit()
{

}
