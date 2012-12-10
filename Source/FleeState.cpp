#include "FleeState.h"

FleeState::FleeState(NPC *owner) :
	FSMState<NPC>(owner)
{

}

void FleeState::Enter()
{
	counter = 5;
	owner->MoveTo(owner->grid->GetFreeNode());
	owner->name = tolower(owner->name);
}

void FleeState::Update()
{
	
	if (owner->currentNode == owner->enemy->currentNode)
	{
		owner->ChangeState(owner->chaseState);
		return;
	}

	if (counter <= 0)
	{
		counter = 5;
		GridNode *next;

		while (next = owner->grid->GetFreeNode())
		{
			if (next->npc == NULL)
				break;
		}

		owner->MoveTo(next);
	}
	else
	{
		counter--;
	}
}

void FleeState::Exit()
{
}
