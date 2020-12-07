#include "Include/Screens.h"
#include "Include/Character.h"
#include "Include/Engine.h"
#include "Include/Map.h"
#include "BearLibTerminal/BearLibTerminal.hpp"

#include <stdbool.h>

const short VIEW_DUNGEON_WIDTH = 65;
const short VIEW_DUNGEON_HEIGHT = 19;

/* title screen */
void ShowTitleScreen( )
{
    TerminalClear();

    TerminalPrint(36, 12, "The Ship");
    TerminalColor(ColorFromName("orange"));
    TerminalPrint(28, 14, "Press Space to continue");

    TerminalRefresh();

    _Bool running = true;

    // Handle event for title screen
    while ( running )
    {
        int key = TerminalRead();

        if (key == TK_SPACE)
        {
            running = false;
        }
        // The user close the window
        else if (key == TK_CLOSE)
        {
            running = false;
            ExitApplication( 0 );
        }
    }
}

/* character choice menu */
int ShowWorldChoice( )
{
    TerminalClear();

    TerminalColor(ColorFromName("white"));
    TerminalPrint( 2, 2, "Choose your homeworld:");

    TerminalColor(ColorFromName("orange"));
    TerminalPrintF(5, 4, "E[color=white]arth (1.00G)");
    TerminalPrintF(5, 6, "N[color=white]ew Beijing (0.87G)");
    TerminalPrintF(5, 8, "S[color=white]parta (1.31G)");

    TerminalRefresh();

    while ( true )
    {
        int c = TerminalRead();

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
            ExitApplication( 0 );
        }
    }
}

/* regiment choice menu */
int ShowRegimentChoice( )
{
    TerminalClear();

    TerminalColor(ColorFromName("white"));
    TerminalPrint(2, 2, "Choose your regiment:");

    TerminalPrintF(5, 4, "[color=orange]C[/color]ommando");
    TerminalPrintF(5, 6, "[color=orange]M[/color]edic");
    TerminalPrintF(5, 8, "[color=orange]S[/color]apper");
    TerminalPrintF(5, 10, "[color=orange]T[/color]echnician");
    TerminalPrintF(5, 12, "[color=orange]H[/color]igh Command");
    TerminalPrintF(5, 14, "[color=orange]E[/color]ngineer");

    TerminalRefresh();

    while ( true )
    {
        int c = TerminalRead();

        if ( c == TK_C )
        {
            return COM;
        }
        else if ( c == TK_M )
        {
            return MED;
        }
        else if ( c == TK_S )
        {
            return SAP;
        }
        else if ( c == TK_T )
        {
            return TEC;
        }
        else if ( c == TK_H )
        {
            return HIG;
        }
        else if ( c == TK_E )
        {
            return ENG;
        }
    }
}

/* create main game screen */
void ShowMainScreen( )
{
    TerminalClear();

    ShowBorderLine();
    ShowStatsCharacter( );
    ShowStatusGuns( );
    DrawDungeon();

    TerminalRefresh();
}

void ShowBorderLine()
{
    // Border line for horizontal
    for (int i = 0; i < 80; i++)
    {
        // Representation of character 205 in encoding cp437.
        TerminalPut(i, 19, 205);
    }

    // Border line for vertical
    for (int j = 0; j < 19; j++)
    {
        // Representation of character 186 in encoding cp437.
        TerminalPut(65, j, 186);
    }

    // Border line in the intercept with the horizontal and vertical.
    // Representation of character 202 in encoding cp437.
    TerminalPut(65, 19, 202);
}

/* print a message to the 2-line message bar at top of screen */
void print_msg ( char *msg )
{
    /* write new message */
    write_string ( 0, 0, msg, ColorFromName("grey") );
    TerminalRefresh();
}
