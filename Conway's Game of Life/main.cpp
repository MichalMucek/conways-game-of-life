#include <cstdio>

#include "CellGrid.h"


int main()
{
	gol::CellGrid cellGrid(30, 30);
	cellGrid.reviveCell(0, 1);
	cellGrid.reviveCell(1, 2);
	cellGrid.reviveCell(2, 0);
	cellGrid.reviveCell(2, 1);
	cellGrid.reviveCell(2, 2);
	cellGrid.reviveCell(15, 13);
	cellGrid.reviveCell(15, 14);
	cellGrid.reviveCell(15, 15);
	cellGrid.print();
	getchar();

	while (true)
	{
		cellGrid.updateOnce();
		cellGrid.print();
		//getchar();
	}
}