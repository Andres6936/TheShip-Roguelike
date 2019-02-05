#include <stdlib.h>
#include <assert.h>

#include "Include/Dice.h"

/*
 * Returns a number which is equivalent to rolling a
 * dice like, '3d4+5' where num_dice = 3, num_sides = 4, mod = 5
 */
int roll_dice ( int num_dice, int num_sides, int mod )
{
    int rnum = 0;

    assert ( num_dice > 0 );
    assert ( num_sides > 0 );
    assert ( mod >= 0 );

    for ( int i = 0; i < num_dice; i++ )
    {
        int frnum = num_inrange ( 1,num_sides );
        rnum += frnum;
    }
    return rnum + mod;
}

/* returns a number in the range, lowest >= num <= highest  */
int num_inrange ( int lowest, int highest )
{
    int rnum;

    assert ( lowest < highest );

    rnum = lowest + ( int ) ( random() % ( highest + 1 ) );

    return rnum;
}
