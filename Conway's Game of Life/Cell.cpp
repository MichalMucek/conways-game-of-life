#include "Cell.h"


gol::Cell::Cell()
{
}

gol::Cell::~Cell()
{
}

bool gol::Cell::isAlive()
{
	return alive;
}

void gol::Cell::kill()
{
	alive = false;
}

void gol::Cell::revive()
{
	alive = true;
}