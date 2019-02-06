#include "Include/Map.h"
#include "Include/Tile.h"
#include "Include/Engine.h"
#include "Include/Object.h"
#include "Include/Logger.h"
#include "Include/Screens.h"
#include "Include/Character.h"
#include "Include/BearLibTerminal.h"

#include <assert.h>

mapchar mapmap[8];

object *lev1 = NULL;

// Dimension of dungeon (map).
const unsigned short DUNGEON_COLUMN = 65;
const unsigned short DUNGEON_ROW = 19;

// NOTE: Error to used const in dungeon.
// Represent of map.
Tile dungeon[65][19] = {};

extern int location[];

/* set up the character mapping */
void set_mapdrawing_chars()
{
    mapchar mc;

    mapchar blank = {0, '\0', WHITE};
    mapmap[BLANK] = blank;

    mapchar wall = {1, '#', D_GREY};
    mapmap[WALL] = wall;

    mapchar floor = {2, '.', L_GREY};
    mapmap[FLR] = floor;

    mc.unum = 3;
    mc.symbol = '<';
    mc.color = WHITE;
    mapmap[UPSTR] = mc;

    mc.unum = 4;
    mc.symbol = '>';
    mc.color = WHITE;
    mapmap[DNSTR] = mc;

    mc.unum = 5;
    mc.symbol = '+';
    mc.color = WHITE;
    mapmap[CDOOR] = mc;

    mc.unum = 6;
    mc.symbol = '|';
    mc.color = WHITE;
    mapmap[ODOOR] = mc;
}

void CreateDungeon( )
{
    // Tile for defect for the map.
    Tile WALL_TILE = {'.'};

    for( int x = 0; x < DUNGEON_COLUMN; x++)
    {
        for( int y = 0; y < DUNGEON_ROW; y++)
        {
            dungeon[x][y] = WALL_TILE;
        }
    }
}

/* open a door */
int open_door()
{

    int doorxloc, dooryloc;
    char loc_char;

    print_msg ( "Which direction?" );

    for ( ;; )
    {
        int c = terminal_read();
        int no_dir = 1;

        if ( c == 'h' )
        {
            doorxloc = location[0];
            dooryloc = location[1] - 1;
            no_dir = 0;
        }
        if ( c == 'j' )
        {
            doorxloc = location[0] + 1;
            dooryloc = location[1];
            no_dir = 0;
        }
        if ( c == 'k' )
        {
            doorxloc = location[0] - 1;
            dooryloc = location[1];
            no_dir = 0;
        }
        if ( c == 'l' )
        {
            doorxloc = location[0];
            dooryloc = location[1] + 1;
            no_dir = 0;
        }
        if ( c == 'y' )
        {
            doorxloc = location[0] - 1;
            dooryloc = location[1] - 1;
            no_dir = 0;
        }
        if ( c == 'u' )
        {
            doorxloc = location[0] - 1;
            dooryloc = location[1] + 1;
            no_dir = 0;
        }
        if ( c == 'b' )
        {
            doorxloc = location[0] + 1;
            dooryloc = location[1] - 1;
            no_dir = 0;
        }
        if ( c == 'n' )
        {
            doorxloc = location[0] + 1;
            dooryloc = location[1] + 1;
            no_dir = 0;
        }

        if ( no_dir == 1 )
        {
            print_msg ( "Interesting direction..." );
            return -1;
        }
    }
}

void DrawDungeon( )
{
    // Clear the area of map only.
    terminal_clear_area(0, 0, DUNGEON_COLUMN, DUNGEON_ROW);

    // Draw the dungeon.
    for ( int x = 0; x < DUNGEON_COLUMN; x++ )
    {
        for ( int y = 0; y < DUNGEON_ROW; y++ )
        {
            terminal_put(x, y, dungeon[x][y].glyph);
        }
    }
}
