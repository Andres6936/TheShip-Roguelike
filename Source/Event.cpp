#include "Include/Event.h"

void HandlerEvent( int key )
{
    // Movement of player (user).
    if ( key == TK_UP )
    {
        Walk(NORTH);
    }
    if ( key == TK_DOWN )
    {
        Walk(SOUTH);
    }
    if ( key == TK_LEFT )
    {
        Walk(WEST);
    }
    if ( key == TK_RIGHT )
    {
        Walk(EAST);
    }

    // NOTE: Fix code.

    /* pick up objects from the floor */
    if ( key == TK_COMMA )
    {
        get_from_flr();
    }
    if ( key == TK_I )
    {
        //show_inventory();
    }
}
