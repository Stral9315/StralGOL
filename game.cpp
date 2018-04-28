#include <game.h>
#include <stdlib.h>

Grid::Grid()
{
	this->cells = nullptr;
	this->rows = 0;
	this->columns = 0;
}

Grid::Grid(int64_t _columns, int64_t _rows)
{
	//cells = (Cell*)malloc(_rows * _columns * sizeof(Cell));
	cells = new Cell[_rows*_columns];
	rows = _rows;
	columns = _columns;

	for( int64_t col = 0; col < columns; col++ )
	{
		for( int64_t row = 0; row < rows; row++ )
		{
			Cell *p = cellAt(col, row);
			p->living = false;
			p->neighbourCount = 0;
		}
	}

}

Grid::~Grid()
{
	delete[] cells;
}

bool Grid::_withinBounds(int64_t _col, int64_t _row)
{
	return (_col >= 0 && _col < columns && _row >= 0 && _row < rows);
}


bool Grid::cellAliveAt(int64_t _col, int64_t _row)
{
	if( !_withinBounds(_col, _row) )
		return false;
	Cell *p = cellAt(_col, _row);
	return p->living;
}

//Return pointer to grid cell at column, row
//out of bounds will return nullptr
Cell* Grid::cellAt(int64_t _col, int64_t _row)
{
	if( !_withinBounds(_col, _row) )
		return nullptr;
	return cells + (_col + _row*columns);
}


//Updates cell at _columns/_rows position and also returns neighbour count 
uint8_t Grid::cellNeighbourCount(int64_t _columns, int64_t _rows)
{
	Cell* cell = cellAt(_columns, _rows);
	cell->neighbourCount = 0;
	for( int64_t x = -1; x < 2; x++ )
	{
		for( int64_t y = -1; y < 2; y++ )
		{
			Cell* p = cellAt(_columns + x, _rows + y);
			if( p /*not out of bounds or other error*/ && p->living && p != cell /*dont count itself*/ )
				cell->neighbourCount++;
		}
	}
	return cell->neighbourCount;
}



//set cell at _col/_row to be living or dead
void Grid::cellSet(int64_t _col, int64_t _row, bool _val)
{
	Cell *p = cellAt(_col, _row); //move _col times, and then an entire row for each _row
	if(p)
	{
		p->living = _val;
		cellNeighbourCount(_col, _row);
	}
}


Grid* Grid::simulate()
{
	Grid* newGrid = new Grid(columns, rows);
	for( int64_t col = 0; col < columns; col++ )
	{ //optimization: keep a list of living cells and draw only those. also maybe could loop through only those as well
		for( int64_t row = 0; row < rows; row++ )
		{
			bool living = false;
			uint8_t count = cellNeighbourCount(col, row);
			newGrid->cellSet(col, row, living = cellAliveAt(col, row));

			if( living && (count < 2 || count > 3)) //underpopulation or overpopulation death
			{
				newGrid->cellSet(col, row, false);
			}
			else if( !living && count == 3 )
			{
				newGrid->cellSet(col, row, true);
			}
		}
	}
	return newGrid;
}
