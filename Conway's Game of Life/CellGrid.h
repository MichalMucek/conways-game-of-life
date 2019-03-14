#pragma once
#include <vector>

#include "Cell.h"


namespace gol {
	class CellGrid
	{
		int rowCount, columnCount;
		std::vector<std::vector<Cell>> grid;

	public:
		CellGrid(int rowCount, int columnCount);
		~CellGrid();
		void print();
		void updateOnce();
		void update(int updateIterationsCount);
		void killCell(int row, int column);
		void reviveCell(int row, int column);
	};
}