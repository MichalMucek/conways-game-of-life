#pragma once
#include <vector>

#include "Cell.h"

namespace fs = std::filesystem;


namespace gol {
	class CellGrid
	{
		int rowCount, columnCount;
		std::vector<std::vector<Cell>> grid;

		void updateSize();
		void setRowCountFromPatternFileAndMovePositionPointerColumnCount(std::fstream &patternFile);
		void setColumnCountFromPatternFileAndMovePositionPointerToEncodedPatternString(std::fstream &patternFile);
		std::string getEncodedPatternStringFromPatternFile(std::fstream &patternFile);

	public:
		CellGrid();
		CellGrid(fs::path filepath);
		CellGrid(int rowCount, int columnCount);
		~CellGrid();
		void printToStandardOutput();
		void updateOnce();
		void updateManyTimes(int updateIterationsCount);
		void killCell(int row, int column);
		void reviveCell(int row = 0, int column = 0);
		bool putHorizontalPropeller(int row = 0, int column = 0);
		bool putVerticalPropeller(int row = 0, int column = 0);
		bool putGlider(int row = 0, int column = 0);
		void setWithDefaultSizeAndPattern();
		std::string getPatternString();
		void setCellsStateFromPatternString(std::string patternString);
	};
}