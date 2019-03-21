#include <cstdio>

#include "CellGrid.h"


int main()
{
	gol::CellGrid cellGrid(30, 30);
	cellGrid.putVerticalPropeller(1, 29);
	
	cellGrid.print();
	getchar();

	while (true)
	{
		cellGrid.updateOnce();
		cellGrid.print();
		//getchar();
	}
}