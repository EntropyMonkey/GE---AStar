#include "Grid.h"

using namespace std;

Grid::Grid()
{
	alpha.name = "A";

	Create(8, 8);
	DrawToConsole();

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

	alpha.currentNode = nodes[0];
	alpha.targetNode = nodes[width * height - 1];
	alpha.currentNode->npc = &alpha;
}

void Grid::AddNode(int x, int y)
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

bool Grid::Update()
{
	Sleep(1000);

	alpha.CalculateTurnActions();

	DrawToConsole();
	return true;
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
}
