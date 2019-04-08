#include <cstdio>
#include <filesystem>

#include "CellGrid.h"

namespace fs = std::filesystem;

int main()
{
	fs::path lastStatePath("gridLastState.txt");
	fs::path Copperhead_30x12_Path("30x12_copperhead.txt");
	gol::CellGrid cellGrid;
	
	if (fs::exists(lastStatePath) && fs::is_regular_file(lastStatePath))
		cellGrid = gol::CellGrid(lastStatePath);
	else
		cellGrid = gol::CellGrid(Copperhead_30x12_Path);
	
	cellGrid.printToStandardOutput();
	std::getchar();

	for (int i = 0; i < 50; i++)
	{
		cellGrid.updateOnce();
		cellGrid.printToStandardOutput();
	}

	return 0;
}