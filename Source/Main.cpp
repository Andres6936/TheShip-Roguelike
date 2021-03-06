#include <stdbool.h>

#include "Include/Engine.h"
#include "Include/Object.h"
#include "Include/Map.h"
#include "Include/Logger.h"
#include "Include/Character.h"
#include "Include/Screens.h"
#include "Include/Event.h"
#include "BearLibTerminal/BearLibTerminal.hpp"

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
        int key = TerminalRead();

        // The user close the window.
        if ( key == TK_CLOSE )
        {
            break;
        }

        HandlerEvent(key);

        ShowStatsCharacter( );
        ShowStatusGuns( );
        DrawDungeon();
        TerminalRefresh();
    }

    ExitApplication( 0 );

    return 1;
}
