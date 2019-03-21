#include <cstdio>

#include "CellGrid.h"


int main()
{
	gol::CellGrid cellGrid(30, 10);
	cellGrid.putGlider(0, 0);
	
	cellGrid.print();
	getchar();

	while (true)
	{
		cellGrid.updateOnce();
		cellGrid.print();
		//getchar();
	}
}