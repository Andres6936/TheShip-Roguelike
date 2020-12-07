#include "Include/Map.h"
#include "Include/Tile.h"
#include "Include/Engine.h"
#include "Include/Object.h"
#include "Include/Logger.h"
#include "Include/Screens.h"
#include "Include/Character.h"
#include "BearLibTerminal/BearLibTerminal.hpp"

#include <assert.h>

mapchar mapmap[8];

object *lev1 = NULL;

// Dimension of dungeon (map).
const unsigned short DUNGEON_WIDTH = 100;
const unsigned short DUNGEON_HEIGHT = 100;

// NOTE: Error to used const in dungeon.
// Represent of map.
Tile dungeon[100][100] = {};

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

    for( int x = 0; x < DUNGEON_WIDTH; x++)
    {
        for( int y = 0; y < DUNGEON_HEIGHT; y++)
        {
            dungeon[x][y] = WALL_TILE;
        }
    }
}

// NOTE: Rename method.
void DrawDungeon( )
{
    // Clear the area of map only.
	TerminalClearArea(0, 0, VIEW_DUNGEON_WIDTH, VIEW_DUNGEON_HEIGHT);

    // Reference: http://www.roguebasin.com/index.php?title=Scrolling_map.
    // Need draw the portion map visible and center to player.
    // This called Scrolling map.

    int startX = player.x - (VIEW_DUNGEON_WIDTH / 2);
    int startY = player.y - (VIEW_DUNGEON_HEIGHT / 2);

    if (player.x < VIEW_DUNGEON_WIDTH / 2)
    {
        startX = 0;
    }
    else if (player.x >= DUNGEON_WIDTH - (VIEW_DUNGEON_WIDTH / 2))
    {
        startX = DUNGEON_WIDTH - VIEW_DUNGEON_WIDTH;
    }

    if (player.y < VIEW_DUNGEON_HEIGHT / 2)
    {
        startY = 0;
    }
    else if (player.y >= DUNGEON_HEIGHT - (VIEW_DUNGEON_HEIGHT / 2))
    {
        startY = DUNGEON_HEIGHT - VIEW_DUNGEON_HEIGHT;
    }

    for ( int x = 0; x < VIEW_DUNGEON_WIDTH; x++ )
    {
        for ( int y = 0; y < VIEW_DUNGEON_HEIGHT; y++ )
        {
            TerminalPut(x, y, dungeon[x + startX][y + startY].glyph);
        }
    }

    // Draw the player in the center.
    // Exist an exception and is when the player is in the edge of map.
    TerminalPut(player.x - startX, player.y - startY, player.glyph);
}
