#include <common.h>
#include <stdlib.h>
#include <stdio.h>
#include <stralGOL.h>
#include <curses.h>

int main( int _argc, char* _argv[] )
{
	
	
	printf("Version: %d.%d\n", StralGOL_VERSION_MAJOR, StralGOL_VERSION_MINOR);

	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();
	curs_set(0);

	int i = 0;
	int vel = 1;
	int row = 1;
	int a = 0;
	int gravity = 2;
	while( getch() == ERR )
	{
		a++;
		erase();
		i += vel;
		if( a % 2 == 0 )
			row++;
		if( i+5 > getmaxx(stdscr) || i < 0 )
		{
			vel *= -1;
			row++;
			if( row > getmaxy(stdscr) )
			{
				row = 1;
			}
		}
		mvaddstr(row, i, "cool");
		
		refresh();
		napms(8);
		
	}

	return 0;
}