#include "Include/Screens.h"
#include "Include/Character.h"
#include "Include/Engine.h"
#include "Include/Map.h"
#include "Include/BearLibTerminal.h"

#include <stdbool.h>

/* title screen */
void ShowTitleScreen( )
{
    terminal_clear();

    terminal_print(36, 12, "The Ship");
    terminal_color(color_from_name("orange"));
    terminal_print(28, 14, "Press Space to continue");

    terminal_refresh();

    _Bool running = true;

    // Handle event for title screen
    while ( running )
    {
        int key = terminal_read();

        if (key == TK_SPACE)
        {
            running = false;
        }
        // The user close the window
        else if (key == TK_CLOSE)
        {
            running = false;
            finish(0);
        }
    }
}

/* character choice menu */
int ShowWorldChoice( )
{
    terminal_clear();

    terminal_color(color_from_name("white"));
    terminal_print( 2, 2, "Choose your homeworld:");

    terminal_color(color_from_name("orange"));
    terminal_printf(5, 4, "E[color=white]arth (1.00G)");
    terminal_printf(5, 6, "N[color=white]ew Beijing (0.87G)");
    terminal_printf(5, 8, "S[color=white]parta (1.31G)");

    terminal_refresh();

    while ( true )
    {
        int c = terminal_read();

        if ( c == TK_E )
        {
            return EAR;
        }
        else if ( c == TK_N )
        {
            return NEW;
        }
        else if ( c == TK_S )
        {
            return SPA;
        }
        else if (c == TK_CLOSE)
        {
            finish(0);
        }
    }
}

/* regiment choice menu */
int ShowRegimentChoice( )
{
    terminal_clear();

    terminal_color(color_from_name("white"));
    terminal_print(2, 2, "Choose your regiment:");

    terminal_printf(5, 4, "[color=orange]C[/color]ommando");
    terminal_printf(5, 6, "[color=orange]M[/color]edic");
    terminal_printf(5, 8, "[color=orange]S[/color]apper");
    terminal_printf(5, 10, "Sc[color=orange]o[/color]ut");
    terminal_printf(5, 12, "[color=orange]T[/color]echnician");
    terminal_printf(5, 14, "[color=orange]H[/color]igh Command");
    terminal_printf(5, 16, "[color=orange]E[/color]ngineer");

    terminal_refresh();

    while ( true )
    {
        int c = terminal_read();

        if ( c == TK_C )
        {
            return COM;
        }
        if ( c == TK_M )
        {
            return MED;
        }
        if ( c == TK_S )
        {
            return SAP;
        }
        if ( c == TK_O )
        {
            return SCO;
        }
        if ( c == TK_T )
        {
            return TEC;
        }
        if ( c == TK_H )
        {
            return HIG;
        }
        if ( c == TK_E )
        {
            return ENG;
        }
    }
}

/* create main game screen */
void ShowMainScreen( )
{
    terminal_clear();

    ShowStatsCharacter( );
    ShowStatusGuns( );
    DrawDungeon();
    DrawPlayer( );

    terminal_refresh();
}

/* print a message to the 2-line message bar at top of screen */
void print_msg ( char *msg )
{
    /* write new message */
    write_string ( 0, 0, msg, color_from_name("grey") );
    terminal_refresh();
}
