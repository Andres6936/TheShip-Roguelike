#include "Include/Event.h"

void HandlerEvent( int key )
{
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
}
