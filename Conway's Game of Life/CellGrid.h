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
		void updateManyTimes(int updateIterationsCount);
		void killCell(int row, int column);
		void reviveCell(int row = 0, int column = 0);
		bool putHorizontalPropeller(int row = 0, int column = 0);
		bool putVerticalPropeller(int row = 0, int column = 0);
		bool putGlider(int row = 0, int column = 0);
	};
}