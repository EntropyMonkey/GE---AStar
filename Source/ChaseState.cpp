#include "ChaseState.h"

ChaseState::ChaseState(NPC *_owner) :
	FSMState<NPC>(_owner)
{

}

void ChaseState::Enter()
{
	owner->name = toupper(owner->name);
}

void ChaseState::Update()
{
	if (owner->currentNode == owner->enemy->currentNode)
	{
		owner->ChangeState(owner->fleeState);
		return;
	}

	owner->MoveTo(owner->grid->FindPathAStar(
		owner->currentNode, owner->enemy->currentNode));
}

void ChaseState::Exit()
{

}
