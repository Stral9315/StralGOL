#include <common.h>
#include <stdlib.h>
#include <stdio.h>
#include <stralGOL.h>
#include <curses.h>
#include <game.h>
#include <string.h>

int main( int _argc, char* _argv[] )
{
	bool glider = false;
	int sleepTime = 400;
	if( _argc > 1 )
	{
		for( uint32_t i = 0; i < _argc; i++ )
		{
			if( !strcmp(_argv[i], "-v") )
				printf("Version: %d.%d\n", StralGOL_VERSION_MAJOR, StralGOL_VERSION_MINOR);
			if( !strcmp(_argv[i], "-test") )
			{
				//TODO: more test shapes
				glider = true;
			}
			if( !strcmp(_argv[i], "-sleeptime") )
			{
				if( ++i < _argc )
				{
					sleepTime = atoi(_argv[i]);
				}
			}
		}
	}
	


	
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();
	curs_set(0);
	refresh();

	int sizeX = getmaxx(stdscr);
	int sizeY = getmaxy(stdscr);
	Grid grid = Grid(sizeX, sizeY);
	Grid* cur = &grid;

	if( glider ) // test
	{
		int xs = 1;
		int ys = 2;
		grid.cellSet(xs, ys, true);
		grid.cellSet(xs + 1, ys, true);
		grid.cellSet(xs + 2, ys, true);
		grid.cellSet(xs + 2, ys - 1, true);
		grid.cellSet(xs + 1, ys - 2, true);
	}
	while( getch() == ERR )
	{
		for( int64_t x = 0; x < sizeX; x++ )
		{
			for( int64_t y = 0; y < sizeY; y++ )
			{
				if( cur->cellAliveAt(x, y) )
				{
					char symbol[2];
					sprintf(symbol, "%d", cur->cellNeighbourCount(x, y));

					mvaddstr(y, x, symbol); //takes y before x for some reason
				}
			}
		}
		refresh();
		napms(sleepTime);
		cur = cur->simulate();
		erase();
	}

	return 0;
}