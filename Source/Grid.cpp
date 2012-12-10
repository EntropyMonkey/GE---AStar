#include "Grid.h"

using namespace std;

Grid::Grid()
{
	alpha = NULL;
	omega = NULL;

	Reset();
}

Grid::~Grid()
{
	delete alpha;
	delete omega;
}

void Grid::Reset()
{
	nodes.clear();

	Create(8, 8);

	if (alpha)
		delete alpha;
	if (omega)
		delete omega;

	alpha = new NPC(nodes[0], 'A');
	omega = new NPC(nodes[width/2 * height/2 + width/2], 'N');

	alpha->enemy = omega;
	omega->enemy = alpha;

	alpha->grid = this;
	omega->grid = this;

	alpha->ChangeState(alpha->chaseState);
	omega->ChangeState(omega->fleeState);
}

void Grid::Create(int _width, int _height)
{
	width = _width;
	height = _height;

	int x, y;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			AddNode(x, y);
		}
	}

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			
			float r = ((float)rand()) / RAND_MAX;
			// a tenth of all gridnodes are blocked
			if (r > 0.9f)
				nodes[y * width + x]->Block();
		}
	}

	Flush();
}

void Grid::AddNode(unsigned int x, unsigned int y)
{
	GridNode *n = new GridNode(x, y);
	nodes.push_back(n);

	// add vertical up connection to both nodes
	if (y > 0)
	{
		Link<GridNode> l;
		l.cost = 1.0f;

		// add to the newly created node
		l.origin = n;
		l.target = nodes[(y-1) * width + x];
		l.origin->AddLink(l);

		// add the connection to the target too
		l.target->AddLink(l.SwitchOriginTarget());
	}

	// add horizontal left connection to both nodes
	if (x > 0)
	{
		Link<GridNode> l;
		l.cost = 1.0f;

		l.origin = n;
		l.target = nodes[y * width + (x-1)];
		l.origin->AddLink(l);

		l.target->AddLink(l.SwitchOriginTarget());
	}
}

GridNode * Grid::GetNode(unsigned int x, unsigned int y)
{
	x = min(x, width - 1);
	y = min(y, height - 1);

	return nodes[x * height + y];
}

GridNode* Grid::GetFreeNode()
{
	int i = (float)rand() / RAND_MAX * (width * height - 1);
	if (nodes[i]->blocked)
		return GetFreeNode();

	return nodes[i];
}

bool Grid::Update()
{
	Sleep(1000);

	alpha->CalculateTurnActions();
	omega->CalculateTurnActions();

	DrawToConsole();
	return true;
}

GridNode* Grid::FindPathAStar(GridNode *start, GridNode *target)
{
	GridNode *current;

	set<GridNode*, GridNode::costCompare> open;
	set<GridNode*, GridNode::costCompare>::iterator openIt;
	list<GridNode*> closed;
	list<GridNode*>::iterator closedIt;
	map<GridNode*, GridNode*> parentChain; // first->child, second->parent

	start->SetCost(0.0f);
	start->SetEstimatedCost(GetDistance(start, target));
	open.insert(start);

	while (open.begin() != open.end() &&
		(current = *(open.begin())) != target)
	{
		open.erase(open.begin());
		current->inOpenSet = false;
		closed.push_back(current);
		//current->inClosedSet = true;

		//current->current = true;

		vector<Link<GridNode> > neighbors = current->GetConnections();

		// test all connected nodes
		for (vector<Link<GridNode> >::iterator link = neighbors.begin();
			link != neighbors.end(); ++link)
		{
			// get the cost for the current path
			float newCost = current->GetCost() + link->cost;
			float oldCost = link->target->GetCost();

			// ignore already worked elements
			if (find(closed.begin(), closed.end(), link->target) 
				!= closed.end())
			{
				continue;
				//link->target->inClosedSet = false;
			}

			// if this path is good
			if ((openIt = find(open.begin(), open.end(), link->target)) 
				!= open.end() &&
				newCost <= oldCost)
			{
				open.erase(openIt);
				//link->target->inOpenSet = false;
			}

			// if the path to the node is better than before, set its parent and new cost
			if (find(open.begin(), open.end(), link->target) == open.end() &&
				find(closed.begin(), closed.end(), link->target) == closed.end())
			{
				link->target->SetCost(newCost);
				open.insert(link->target);
				//link->target->inOpenSet = true;

				// set estimated cost to get to the target
				link->target->SetEstimatedCost(
					newCost + GetDistance(link->target, target));

				// set current as parent for link's target
				parentChain.insert(parentChain.begin(), 
					pair<GridNode*, GridNode*>(link->target, current));
			}
		}
		// debug
		//DrawToConsole();
		//current->current = false;
	}
	
	//PrintPath(parentChain, current);

	list<GridNode *> path;
	GetPath(parentChain, current, path);
	path.erase(path.begin()); // delete start point

	if (path.begin() != path.end())
		return *(path.begin());
	else
		return start;
}

void Grid::Flush()
{
	for (int x = 0; x < width; x++) for (int y = 0; y < height; y++)
	{
		int i = y * width + x;
		/*nodes[i]->inClosedSet = false;
		nodes[i]->inOpenSet = false;
		nodes[i]->current = false;*/
		nodes[i]->SetEstimatedCost(INFINITY);
		nodes[i]->SetCost(INFINITY);
	}
}

float Grid::GetDistance(GridNode *one, GridNode *two)
{
	int x = abs(two->GetCoordX() - one->GetCoordX());
	int y = abs(two->GetCoordY() - one->GetCoordY());
	return sqrt((float)x * x + y * y);
}

void Grid::GetPath(map<GridNode*, GridNode*> &parentChain, 
	GridNode *parent, list<GridNode*> &path)
{
	GridNode *child = parentChain[parent];

	if (child != NULL)
		GetPath(parentChain, child, path);

	path.push_back(parent);
}

void Grid::PrintPath(map<GridNode*, GridNode*> &parentChain, GridNode *parent)
{
	GridNode *child = parentChain[parent];

	if (child != NULL)
		PrintPath(parentChain, child);

	cout << parent->GetCoordX() << "." << parent->GetCoordY() << endl;
}

void Grid::DrawToConsole()
{
	int x = 0;
	int y = 0;

	cout << "\t";
	for(; x < width; x++)
		cout << x << "\t";
	cout << endl;

	x = 0;
	for (; y < height; y++) 
	{
		if (x >= 0)
			cout << y << "\t";

		for (x = 0; x < width; x++)
		{
			
			nodes[y * width + x]->Render();

			cout << "\t";

			if (x == width - 1)
			{
				cout << "\n";
			}
		}
	}

	cout << endl;
}
