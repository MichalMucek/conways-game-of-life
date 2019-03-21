#include <cstdio>

#include "CellGrid.h"


int main()
{
	gol::CellGrid cellGrid(30, 30);
	cellGrid.putGlider(1, 1);
	cellGrid.putHorizontalPropeller(15, 13);
	
	cellGrid.print();
	getchar();

	while (true)
	{
		cellGrid.updateOnce();
		cellGrid.print();
		//getchar();
	}
}