#include <iostream>
#include <string>

#include "CellGrid.h"


gol::CellGrid::CellGrid(int rowCount, int columnCount)
{
	this->rowCount = rowCount;
	this->columnCount = columnCount;
	this->grid.resize(rowCount, std::vector<Cell>(columnCount));
}

gol::CellGrid::~CellGrid()
{
}

void gol::CellGrid::print()
{
	std::string gridView = "";

	system("cls");

	for (int row = 0; row < rowCount; row++)
	{
		for (int column = 0; column < columnCount; column++)
		{
			if (grid[row][column].isAlive())
				gridView += "O ";
			else
				gridView += ". ";

			if (column == columnCount - 1)
				gridView += "\n";
		}
	}

	std::cout << gridView;
}

void gol::CellGrid::updateOnce()
{
	std::vector<std::vector<Cell>> tmpGrid(grid);

	for (int cellRow = 0; cellRow < rowCount; cellRow++)
	{
		for (int cellColumn = 0; cellColumn < columnCount; cellColumn++)
		{
			int aliveNeighbours = 0;

			for (int neighbourRow = cellRow - 1; neighbourRow < cellRow + 2; neighbourRow++)
			{
				if (neighbourRow < 0 || neighbourRow >= rowCount)
					continue;

				for (int neighbourColumn = cellColumn - 1; neighbourColumn < cellColumn + 2; neighbourColumn++)
				{
					if (neighbourColumn < 0 || neighbourColumn >= columnCount || (cellRow == neighbourRow && cellColumn == neighbourColumn))
						continue;

					if (tmpGrid[neighbourRow][neighbourColumn].isAlive())
						aliveNeighbours++;
				}
			}

			if (tmpGrid[cellRow][cellColumn].isAlive() && (aliveNeighbours <= 1 || aliveNeighbours >= 4))
				grid[cellRow][cellColumn].kill();

			if (!tmpGrid[cellRow][cellColumn].isAlive() && aliveNeighbours == 3)
				grid[cellRow][cellColumn].revive();
		}
	}
}

void gol::CellGrid::killCell(int row, int column)
{
	grid[row][column].kill();
}

void gol::CellGrid::reviveCell(int row, int column)
{
	grid[row][column].revive();
}