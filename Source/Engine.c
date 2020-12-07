#include "Include/Engine.h"
#include <BearLibTerminal/BearLibTerminal.hpp>

#include <stdio.h>

void InitEngine ( void )
{
    TerminalOpen();
    TerminalSet("terminal: encoding=437");
    TerminalSet("window: size=80x25, cellsize=auto, title='The Ship'");
}

void WriteChar( int x, int y, char c, color_t color )
{
    TerminalColor( color );
    TerminalPut( x, y, c );
}

/* write a string, 's', to the co-ords (x,y) with colour 'color' */
void write_string ( int x, int y, char *s, color_t color )
{
    TerminalColor( color );
    TerminalPrint( x, y, s );
}

void ExitApplication( const short signal )
{
    TerminalClose();
    printf ( "\nTerminated with signal %i\n\n", signal );
    printf ( "The Ship Version 0.1\n" );
    printf ( "(C) Copyright 2002 Karim Rashad\n" );
    printf ( "All Rights Reserved\n\n" );
}
