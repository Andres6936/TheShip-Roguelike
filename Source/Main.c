#include <stdbool.h>

#include "Include/Engine.h"
#include "Include/Object.h"
#include "Include/Map.h"
#include "Include/Logger.h"
#include "Include/Character.h"
#include "Include/Screens.h"
#include "Include/BearLibTerminal.h"

/*
 * References:
 * http://www.sinergiaderol.com/sumario.html
 * https://es.wikipedia.org/wiki/Categor%C3%ADa:T%C3%A9rminos_de_rol
 * https://es.wikipedia.org/wiki/Categor%C3%ADa:Juegos_de_rol_de_ciencia_ficci%C3%B3n
 * https://es.wikipedia.org/wiki/Categor%C3%ADa:Sistemas_de_juego_de_rol
 */

int main ( int argc, char *argv[] )
{
    char wmsg[] = "You're inside.";
    int w_choice = 0;
    int r_choice = 0;

    WriteLogger ( "Initialising" );
    InitEngine();
    InitObjects();
    set_mapdrawing_chars();
    CreateDungeon( );

    WriteLogger ( "Going to title screen" );
    ShowTitleScreen( );

    WriteLogger ( "Getting origin world" );
    w_choice = ShowWorldChoice( );

    WriteLogger ( "Getting regiment choice" );
    r_choice = ShowRegimentChoice( );

    WriteLogger ( "Rolling PC stats" );
    roll_pc ( w_choice, r_choice );

    WriteLogger ( "Generating starting inventory" );
    gen_sinv ( w_choice, r_choice );

    WriteLogger ( "Deducing secondary stats" );
    gen_secondary_stats();

    WriteLogger ( "Generating starting level" );
    ShowMainScreen( );

    print_msg ( wmsg );

    WriteLogger ( "Entering main game loop" );

    while ( true )
    {
        int key = terminal_read();

        // Pressed C
        if ( key == TK_C )
        {
            // Shift + C
            if (terminal_check(TK_SHIFT))
            {
                terminal_clear();
            }
            // Only C
            else
            {
                terminal_clear();
                write_line ( 4, 30, 20, 'r', color_from_name("red") );
                write_line ( 5, 30, 20, 'g', color_from_name("green") );
                write_line ( 6, 30, 20, 'c', color_from_name("cyan") );
                write_line ( 7, 30, 20, 'g', color_from_name("grey") );
                write_line ( 8, 30, 20, 'b', color_from_name("brown") );
                write_line ( 9, 30, 20, 'b', color_from_name("blue") );
                write_line ( 10, 30, 20, 'm', color_from_name("magenta") );
                write_line ( 11, 30, 20, 'b', color_from_name("black") );
                write_line ( 12, 30, 20, 'o', color_from_name("orange") );
                write_line ( 13, 30, 20, 'g', color_from_name("green") );
                write_line ( 14, 30, 20, 'c', color_from_name("cyan") );
                write_line ( 15, 30, 20, 'w', color_from_name("white") );
                write_line ( 16, 30, 20, 'y', color_from_name("yellow") );
                write_line ( 17, 30, 20, 'b', color_from_name("blue") );
                write_line ( 18, 30, 20, 'p', color_from_name("pink") );
                write_line ( 19, 30, 20, 'g', color_from_name("grey") );
                terminal_refresh();
            }
        }
        else if ( key == TK_LEFT )
        {
            int mtype = move_pc ( 0, -1 );
            if ( mtype == 1 || mtype == 2 )
            {
                print_pc();
            }
        }
        else if ( key == TK_DOWN )
        {
            int mtype = move_pc ( 1, 0 );
            if ( mtype == 1 || mtype == 2 )
            {
                print_pc();
            }
        }
        if ( key == TK_UP )
        {
            int mtype = move_pc ( -1, 0 );
            if ( mtype == 1 || mtype == 2 )
            {
                print_pc();
            }
        }
        if ( key == TK_RIGHT )
        {
            int mtype = move_pc ( 0, 1 );
            if ( mtype == 1 || mtype == 2 )
            {
                print_pc();
            }
        }

        /* open a door */
        if ( key == TK_O )
        {
            open_door();
        }

        /* pick up objects from the floor */
        if ( key == TK_COMMA )
        {
            get_from_flr();
        }

        /* Inventory screen */
        if ( key == TK_I )
        {
            show_inventory();
        }

        /* Quit */
        if ( key == TK_Q || key == TK_CLOSE )
        {
            break;
        }


        DrawDungeon();
        terminal_refresh();
    }

    finish ( 0 );

    return 1;
}
