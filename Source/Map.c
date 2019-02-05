#include "Include/Map.h"
#include "Include/Engine.h"
#include "Include/Object.h"
#include "Include/Logger.h"
#include "Include/Screens.h"
#include "Include/Character.h"
#include "Include/BearLibTerminal.h"

#include <assert.h>

mapchar mapmap[8];

object *lev1 = NULL;

/* an 80x25 screen */
mapchar curr_level[25][80] = {};

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


/* 'blank' map array */
void init_screen_array()
{

    int x,y;

    for ( x = 0; x < 80; x++ )
    {
        for ( y = 0; y < 25; y++ )
        {
            curr_level[y][x] = mapmap[BLANK];
        }
    }
}

void print_map()
{

    draw_lfeats();
    draw_lobjects();
}


/* draw the level objects to the screen */
void draw_lobjects()
{

    int obj_num = 0;
    int numo = object_number ( lev1 );
    char num_msg[20];

    sprintf ( num_msg, "Number: %i", numo );

    if ( lev1 != NULL )
    {
        for ( int c=0; obj_num < object_number ( lev1 ); obj_num++ )
        {
            int xloc = get_xloc ( lev1, obj_num );
            int yloc = get_yloc ( lev1, obj_num );
            char sym = get_look ( lev1, obj_num );
            int col = get_color ( lev1, obj_num );

            WriteChar( xloc, yloc, sym, color_from_name("orange") );
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

/* draw the level from the curr_level array */
void draw_lfeats()
{
    int x,y;
    for ( x = 0; x < 25; x++ )
    {
        for ( y = 0; y < 80; y++ )
        {
            if ( curr_level[x][y].unum != mapmap[BLANK].unum )
            {
                WriteChar( x, y, curr_level[ x ][ y ].symbol, color_from_name("orange") );
            }
        }
    }
}
