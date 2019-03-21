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
	std::vector<std::vector<Cell>> previousGridState(grid);

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

					if (previousGridState[neighbourRow][neighbourColumn].isAlive())
						aliveNeighbours++;
				}
			}

			if (previousGridState[cellRow][cellColumn].isAlive() && (aliveNeighbours <= 1 || aliveNeighbours >= 4))
				grid[cellRow][cellColumn].kill();

			if (!previousGridState[cellRow][cellColumn].isAlive() && aliveNeighbours == 3)
				grid[cellRow][cellColumn].revive();
		}
	}
}

void gol::CellGrid::updateManyTimes(int updateIterationsCount)
{
	for (int i = 0; i < updateIterationsCount; i++)
		updateOnce();
}

void gol::CellGrid::killCell(int row, int column)
{
	grid[row][column].kill();
}

void gol::CellGrid::reviveCell(int row, int column)
{
	grid[row][column].revive();
}

bool gol::CellGrid::putHorizontalPropeller(int row, int column)
{
	if (column + 3 > columnCount) return false;
	
	if (row < 0 || row >= rowCount) row = 0;
	if (column < 0 || column >= columnCount) column = 0;

	reviveCell(row, column); 
	reviveCell(row, column + 1); 
	reviveCell(row, column + 2);

	return true;
}

bool gol::CellGrid::putVerticalPropeller(int row, int column)
{
	if (row + 3 > rowCount) return false;
	
	if (row < 0 || row >= rowCount) row = 0;
	if (column < 0 || column >= columnCount) column = 0;

	reviveCell(row, column);
	reviveCell(row + 1, column);
	reviveCell(row + 2, column);

	return true;
}

bool gol::CellGrid::putGlider(int row, int column)
{
	if (row + 3 > rowCount || column + 3 > columnCount) return false;
	
	if (row < 0 || row >= rowCount) row = 0;
	if (column < 0 || column >= columnCount) column = 0;

	killCell(row, column); reviveCell(row, column + 1); killCell(row, column + 2);
	killCell(row + 1, column); killCell(row + 1, column + 1); reviveCell(row + 1, column + 2);
	reviveCell(row + 2, column); reviveCell(row + 2, column + 1); reviveCell(row + 2, column + 2);

	return true;
}
