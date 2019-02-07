#include "Include/Engine.h"

#include <stdio.h>

void InitEngine ( void )
{
    terminal_open();
    terminal_set("terminal: encoding=437");
    terminal_set("window: size=80x25, cellsize=auto, title='The Ship'");
}

void WriteChar( int x, int y, char c, color_t color )
{
    terminal_color( color );
    terminal_put( x, y, c );
}

/* write a string, 's', to the co-ords (x,y) with colour 'color' */
void write_string ( int x, int y, char *s, color_t color )
{
    terminal_color( color );
    terminal_print( x, y, s );
}

void ExitApplication( const short signal )
{
    terminal_close();
    printf ( "\nTerminated with signal %i\n\n", signal );
    printf ( "The Ship Version 0.1\n" );
    printf ( "(C) Copyright 2002 Karim Rashad\n" );
    printf ( "All Rights Reserved\n\n" );
    exit ( 0 );
}
