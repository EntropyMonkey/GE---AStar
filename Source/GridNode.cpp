#include "GridNode.h"

using namespace std;

GridNode::GridNode(int _x, int _y) :
	x(_x),
	y(_y)
{
	npc = NULL;
	blocked = false;
}

void GridNode::AddLink(GridNode *targetNode, float cost)
{
	Link<GridNode> link;
	link.cost = cost;
	link.origin = this;
	link.target = targetNode;

	connections.push_back(link);
}

void GridNode::AddLink(Link<GridNode> link)
{
	if (link.target != NULL && link.origin == this)
		connections.push_back(link);
}

void GridNode::RemoveLink(GridNode *targetNode)
{
	vector<Link<GridNode> > marked;

	vector<Link<GridNode> >::iterator it;

	for (it = connections.begin();
		it != connections.end();
		it++)
	{
		if (it->target == targetNode)
		{
			marked.push_back(*it);
		}
	}

	// if no connections have been found, don't severe 
	if (marked.size() == 0)
	{
		return;
	}

	for (it = marked.begin(); it != marked.end(); it++)
	{
		connections.erase(find(connections.begin(), connections.end(), *it));
	}
}

GridNode* GridNode::GetNearestNode(std::vector<GridNode*> &visited)
{
	GridNode *nearest = NULL;
	float lowestCost = INT_MAX;

	for (vector<Link<GridNode> >::iterator it = connections.begin();
		it != connections.end(); it++)
	{
		if (find(visited.begin(), visited.end(), it->target) == visited.end() &&
			it->cost < lowestCost)
		{
			nearest = it->target;
			lowestCost = it->cost;
		}
	}

	return nearest;
}

void GridNode::Block()
{
	// a vector to store links marked for deletion
	vector<Link<GridNode> > marked;

	vector<Link<GridNode> >::iterator it;
	
	for (it = connections.begin(); it != connections.end(); it++)
	{
		it->target->RemoveLink(it->origin);
		marked.push_back(*it);
	}

	for (it = marked.begin(); it != marked.end(); it++)
	{
		connections.erase(find(connections.begin(), connections.end(), *it));
	}

	blocked = true;
}

void GridNode::Render()
{
	if (blocked)
		std::cout << "x";
	else if (npc != NULL)
		npc->Render();
}
