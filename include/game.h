#pragma once
#include <common.h>

struct Cell
{
	bool living;
	uint8_t neighbourCount;
};

//Responsible for most of the simulation
class Grid
{
private:
	int64_t columns;
	int64_t rows;
	Cell *cells;
	
	bool _withinBounds(int64_t _col, int64_t _row);
	Cell* cellAt(int64_t _col, int64_t _row);
public:
	Grid();
	~Grid();
	Grid(int64_t _columns, int64_t _rows);
	uint8_t cellNeighbourCount(int64_t _columns, int64_t _rows);
	void cellSet(int64_t _col, int64_t _row, bool _val);
	bool cellAliveAt(int64_t _col, int64_t _row);
	Grid* simulate();
};