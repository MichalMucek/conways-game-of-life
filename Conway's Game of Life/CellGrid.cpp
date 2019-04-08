#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "CellGrid.h"
#include "RLE.h"

namespace fs = std::filesystem;
namespace rle = runLengthEncoding;


gol::CellGrid::CellGrid()
{
	setWithDefaultSizeAndPattern();
}

void gol::CellGrid::setWithDefaultSizeAndPattern()
{
	this->rowCount = 5;
	this->columnCount = 5;
	this->grid.resize(rowCount, std::vector<Cell>(columnCount));
	this->putVerticalPropeller(1, 2);
}

gol::CellGrid::CellGrid(fs::path filepath)
{
	std::fstream patternFile;
	std::string encodedPatternString;
	std::string decodedPatternString;

	if (fs::exists(filepath) && fs::is_regular_file(filepath))
	{
		patternFile.open(filepath.c_str(), std::ios::in);

		if (patternFile.good())
		{
			setRowCountFromPatternFileAndMovePositionPointerColumnCount(patternFile);
			setColumnCountFromPatternFileAndMovePositionPointerToEncodedPatternString(patternFile);
			updateSize();

			encodedPatternString = getEncodedPatternStringFromPatternFile(patternFile);
			decodedPatternString = rle::decode(encodedPatternString);

			setCellsStateFromPatternString(decodedPatternString);

			patternFile.close();
		}
	}
	else
	{
		setWithDefaultSizeAndPattern();

		std::cout << "!!! ERROR: FAILED READING PATTERN FILE !!!" << std::endl
			<< "*** INFO: DEFAULT GRID WAS LOADED ***" << std::endl;

		system("pause");
	}
}

void gol::CellGrid::setRowCountFromPatternFileAndMovePositionPointerColumnCount(std::fstream &patternFile)
{
	patternFile >> this->rowCount;
}

void gol::CellGrid::setColumnCountFromPatternFileAndMovePositionPointerToEncodedPatternString(std::fstream &patternFile)
{
	patternFile >> this->columnCount;
}

void gol::CellGrid::updateSize()
{
	this->grid.resize(this->rowCount, std::vector<Cell>(this->columnCount));
}

std::string gol::CellGrid::getEncodedPatternStringFromPatternFile(std::fstream &patternFile)
{
	std::string encodedPatternString;

	patternFile >> encodedPatternString;

	return encodedPatternString;
}

void gol::CellGrid::setCellsStateFromPatternString(std::string patternString)
{
	for (int row = 0, characterIndex = 0; row < rowCount; row++)
	{
		for (int column = 0; column < columnCount; column++, characterIndex++)
		{
			if (characterIndex < (int)patternString.size())
			{
				if (patternString[characterIndex] == 'A')
					reviveCell(row, column);

				if (patternString[characterIndex] == 'D')
					killCell(row, column);
			}
		}
	}
}

gol::CellGrid::CellGrid(int rowCount, int columnCount)
{
	this->rowCount = rowCount;
	this->columnCount = columnCount;
	this->grid.resize(rowCount, std::vector<Cell>(columnCount));
}

gol::CellGrid::~CellGrid()
{
	std::fstream gridLastStateFile;
	std::string rlePatternCode = "";

	gridLastStateFile.open("gridLastState.txt", std::ios::out);

	if (gridLastStateFile.good())
	{
		gridLastStateFile << this->rowCount << " " << this->columnCount << "\n";

		gridLastStateFile << rle::encode(this->getPatternString());

		gridLastStateFile.close();
	}
}

void gol::CellGrid::printToStandardOutput()
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
				int originalNeighbourRow = neighbourRow;
				
				if (neighbourRow == -1)
					neighbourRow = rowCount - 1;

				if (neighbourRow == rowCount)
					neighbourRow = 0;

				for (int neighbourColumn = cellColumn - 1; neighbourColumn < cellColumn + 2; neighbourColumn++)
				{
					int originalNeighbourColumn = neighbourColumn;
					
					if (cellRow == neighbourRow && cellColumn == neighbourColumn)
						continue;

					if (neighbourColumn == -1)
						neighbourColumn = columnCount - 1;

					if (neighbourColumn == columnCount) 
						neighbourColumn = 0;

					if (previousGridState[neighbourRow][neighbourColumn].isAlive())
						aliveNeighbours++;

					neighbourColumn = originalNeighbourColumn;
				}

				neighbourRow = originalNeighbourRow;
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

std::string gol::CellGrid::getPatternString()
{
	std::string patternString = "";

	for (int row = 0; row < rowCount; row++)
	{
		for (int column = 0; column < columnCount; column++)
		{
			if (grid[row][column].isAlive())
				patternString += "A";
			else
				patternString += "D";
		}
	}
	
	return patternString;
}