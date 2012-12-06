#include <ctime>

#include "Grid.h"

int main()
{
	srand(clock());

	Grid *grid = new Grid();

	while (grid->Update());

	delete grid;

	getchar();

	return 0;
}