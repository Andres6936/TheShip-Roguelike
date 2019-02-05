#include "Include/Character.h"
#include "Include/Engine.h"
#include "Include/Object.h"
#include "Include/Map.h"
#include "Include/Screens.h"
#include "Include/Dice.h"
#include "Include/BearLibTerminal.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * -primary stats
 * max. stat : 50
 */
int char_stats[7] = {0};

/*
 * -secondary stats
 * max stats:
 * S: 100
 * A: 99/99
 * C: 999/999
 * L: 999/999
 * D: 99
 * XL: 50
 */
int sec_stats[12] = {0};

/* pc's location - current_x, current_y, last_x, last_y */
int location[4] = {7,45,6,46};

object *inventory = NULL; /* inventory list */
object equip[7];

extern object *lev1;
extern mapchar curr_level[25][80];

/* roll the PCs starting stats; */
void roll_pc ( int class, int regiment )
{
    int i;
    /* array of how to modify the RNG's initial rolls */
    static int mod_stats[7] = {0};

    if ( class == EAR )
    {
        mod_stats[STR] = -3;
        mod_stats[CUN] = 0;
        mod_stats[INT] = 3;
        mod_stats[CON] = -1;
        mod_stats[VIS] = -1;
        mod_stats[SPE] = 0;
        mod_stats[CHA] = 0;
    }
    if ( class == NEW )
    {
        mod_stats[STR] = 3;
        mod_stats[CUN] = 1;
        mod_stats[INT] = -2;
        mod_stats[CON] = 1;
        mod_stats[VIS] = 1;
        mod_stats[SPE] = 0;
        mod_stats[CHA] = -2;
    }
    if ( class == SPA )
    {
        mod_stats[STR] = -3;
        mod_stats[CUN] = 1;
        mod_stats[INT] = 3;
        mod_stats[CON] = -1;
        mod_stats[VIS] = -1;
        mod_stats[SPE] = 1;
        mod_stats[CHA] = 0;
    }

    for ( i=0; i<7; i++ )
    {
        char_stats[i] = roll_dice ( 1,14,2 );
        char_stats[i] += mod_stats[i];
    }
}


/* prints the primary stats array to the screen */
void ShowStatsCharacter( )
{
    // NOTE: Is necessary verify that the integers no have more two digits.

    char strong[3];
    char cunning[3];
    char intelligence[3];
    char constitution[3];
    char vision[3];
    char speed[3];
    char chakra[3];

    // Convert the integers to string for show in terminal

    sprintf(strong, "%2d", char_stats[STR]);
    sprintf(cunning, "%2d", char_stats[CUN]);
    sprintf(intelligence, "%2d", char_stats[INT]);
    sprintf(constitution, "%2d", char_stats[CON]);
    sprintf(vision, "%2d", char_stats[VIS]);
    sprintf(speed, "%2d", char_stats[SPE]);
    sprintf(chakra, "%2d", char_stats[CHA]);

    terminal_color(color_from_name("white"));

    terminal_printf(75, 3, strong);
    terminal_printf(75, 5, cunning);
    terminal_printf(75, 7, intelligence);
    terminal_printf(75, 9, constitution);
    terminal_printf(75, 11, vision);
    terminal_printf(75, 13, speed);
    terminal_printf(75, 15, chakra);
}

void ShowStatusGuns( )
{
    // NOTE: Is necessary verify that the integers no have more three digits.

    char laserI[4];
    char laserII[4];

    char cannonI[4];
    char cannonII[4];

    // NOTE: Is necessary verify that the integers no have more two digits.

    char armorI[3];
    char armorII[3];

    char speedI[3];
    char speedII[3];

    char damageI[3];
    char damageII[3];

    // Convert the integers to string for show in terminal.

    // Convert the integers to string with format: '999/999'.
    sprintf(laserI, "%3d/999", sec_stats[L1]);
    sprintf(laserII, "%3d/999", sec_stats[L2]);

    // Convert the integers to string with format: '999/999'.
    sprintf(cannonI, "%3d/999", sec_stats[C1]);
    sprintf(cannonII, "%3d/999", sec_stats[C2]);

    // Convert the integers to string with format: '99/ 99'.
    sprintf(armorI, "%2d/ 99", sec_stats[A1]);
    sprintf(armorII, "%2d/ 99", sec_stats[A2]);

    // Convert the integers to string with format: '99'.
    sprintf(speedI, "%2d", sec_stats[SP]);
    sprintf(speedII, "%2d", sec_stats[SP]);

    // Convert the integers to string with format: '99'.
    sprintf(damageI, "%2d", sec_stats[DG]);
    sprintf(damageII, "%2d", sec_stats[DG]);


    terminal_color(color_from_name("white"));

    // Laser:
    terminal_printf(26, 22, laserI);
    terminal_printf(26, 23, laserII);

    // Cannon:
    terminal_printf(36, 22, cannonI);
    terminal_printf(36, 23, cannonII);

    // Armor:
    terminal_printf(47, 22, armorI);
    terminal_printf(47, 23, armorII);

    // Speed:
    terminal_printf(59, 22, speedI);
    terminal_printf(59, 23, speedII);

    // Damage:
    terminal_printf(69, 22, damageI);
    terminal_printf(69, 23, damageII);
}

/* generate initial secondary stats */
void gen_secondary_stats()
{

    /* Experience initial */
    sec_stats[XP] = 0;
    sec_stats[XL] = 1;

    /* Life points initial calculation  */
    sec_stats[L1] = sec_stats[L2] = char_stats[CON] + ( char_stats[STR] / 4 );

    /* Concentration points initial calculation  */
    sec_stats[C1] = sec_stats[C2] = char_stats[INT] + roll_dice ( 1,6,0 );
    /*** plus class modifiers ***/

    /* Armour initial Calculation  */
    sec_stats[A1] = 3;
    sec_stats[A2] = 4;

    /* Speed initial calculation  */
    sec_stats[SP] = char_stats[SPE] + ( char_stats[CUN] / 4 ) + 50;

    /* Dodge initial calculation  */
    sec_stats[DG] = sec_stats[SP] + char_stats[STR] + char_stats[VIS];
}


/* write pc to present location */
/* also writes last sq. */
void print_pc()
{
    mapchar last_loc;
    int lastx, lasty;
    int onum;

    /* present location */
    WriteChar( location[ 0 ], location[ 1 ], '@', color_from_name("red") );

    /* last square */
    lastx = location[2];
    lasty = location[3];

    /* this is FUCKED */
    onum = object_present ( lev1, lastx, lasty );
    if ( onum != -1 )
    {
        WriteChar( location[ 2 ], location[ 3 ], get_look( lev1, onum ), color_from_name("orange"));
    }
    else
    {
        last_loc = curr_level[lastx][lasty];
        WriteChar( location[ 2 ], location[ 3 ], last_loc.symbol, color_from_name("orange") );
    }
}

/*
 * shift location by x,y
 * -returns code of any obstacles/monster
 * 0 : don't move; wall
 * 1 : OK to move normally; empty square
 * 2 : object on floor
 * 3 : a closed door
 */
int move_pc ( int x, int y )
{
    int xfloc =  location[0] + x;
    int yfloc =  location[1] + y;
    /* get symbol at intended location */
    int iloc = terminal_pick(xfloc, yfloc, 1);

    /* a wall */
    if ( iloc == '#' )
    {
        print_msg ( "That's a wall." );
        return 0;
    }

    /* a closed door */
    if ( iloc == '+' )
    {
        print_msg ( "You bump into the door." );
        return 3;
    }

    /* an object */
    if ( iloc == '(' || iloc == ')' || iloc == '/' || iloc == '\\' || iloc == '%' || iloc == '$' || iloc == '!' || iloc == '?' )
    {
        char *namebuf;
        if ( lev1 != NULL )
        {
            char *obj_name = get_oname ( lev1, get_unum ( lev1, xfloc, yfloc ) );
            char obj_msg[30] = "You see a ";
            char *obj_end = ".";
            strcat ( obj_msg, obj_name );
            namebuf = ( char * ) strcat ( obj_msg, obj_end );
        }
        else
        {
            namebuf = NULL;
        }
        print_msg ( namebuf );
        location[2] = location[0];
        location[3] = location[1];
        location[0] += x;
        location[1] += y;
        return 2;
    }
    else
    {
        /* clear message bar on movement */
        print_msg ( "" );
    }

    /* if OK, go ahead and change location */
    location[2] = location[0];
    location[3] = location[1];
    location[0] += x;
    location[1] += y;
    return 1;
}

/* returns unum of item picked up */
int get_from_flr()
{
    object *prev_obj_ptr, *current_obj_ptr;
    const char obj_msg[30] = "You pick up the ";

    if ( lev1 == NULL )
    {
        print_msg ( "There's nothing here." );
        return -1;
    }

    if ( lev1->xloc == location[0] && lev1->yloc == location[1] )
    {
        char *msg;
        int ounum = lev1->unum;
        const char *obj_name = get_oname ( lev1, ounum );
        const char *msg_end = ".";
        strcat ( obj_msg, obj_name );
        msg = ( char * ) strcat ( obj_msg, msg_end );
        print_msg ( msg );

        /* remove from floor list, put in inventory list */
        inventory = insert_obj ( inventory, lev1 );
        lev1 = delete_obj ( lev1, lev1->unum );

        return ounum;
    }
    else
    {
        prev_obj_ptr = lev1;
        current_obj_ptr = lev1->next_obj;
        while ( current_obj_ptr != NULL && ( current_obj_ptr->xloc != location[0] || current_obj_ptr->yloc != location[1] ) )
        {
            prev_obj_ptr = current_obj_ptr;
            current_obj_ptr = current_obj_ptr->next_obj;
        }
        if ( current_obj_ptr != NULL )
        {
            char *msg;
            int ounum = current_obj_ptr->unum;
            const char *obj_name = get_oname ( current_obj_ptr, ounum );
            const char *msg_end = ".";
            strcat ( obj_msg, obj_name );
            msg = ( char * ) strcat ( obj_msg, msg_end );
            print_msg ( msg );

            /* remove from floor list, put in inventory list */
            inventory = insert_obj ( inventory, lev1 );
            lev1 = delete_obj ( lev1, current_obj_ptr->unum );

            return ounum;
        }
    }
    return -1;
}