/* object manipulation function definitions */

#include "Include/Object.h"
#include "Include/Character.h"
#include "Include/Engine.h"
#include "Include/Screens.h"
#include "BearLibTerminal/BearLibTerminal.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* weapon lists */
object srw[3];
object lrw[2];

/* player associated arrays */
extern object *inventory; /* inventory list */

/*
 * equiped items slots
 *
 * 0 - short range weapon - SRW
 * 1 - long range weapon  - LRW
 * 2 - body armour        - ARM
 * 3 - head gear          - HDA
 * 4 - leg wear           - LGA
 * 5 - foot wear          - FTA
 * 6 - ammo               - AMM
 */
extern object equip[];
extern int location[];
extern object *lev1;

/* linked list stuff */

/*
 * inserts a object into a linked list,
 * remember to create the list by initialising
 * the starting pointer to NULL, and setting
 * the starting pointer to the return value of
 * insert_obj();
 */
object *insert_obj ( object *olist_ptr, object *obj_ptr )
{
    /* insert new node at start of list; move list ptr to start of list */
    obj_ptr->next_obj = olist_ptr;
    olist_ptr = obj_ptr;

    return olist_ptr;
}

object *delete_obj ( object *olist_ptr, int obj_num )
{
    object *prev_obj_ptr, *current_obj_ptr, *temp_obj_ptr;

    if ( obj_num == olist_ptr->unum )
    {
        temp_obj_ptr = olist_ptr;
        if ( olist_ptr->next_obj == NULL )
        {
            olist_ptr = NULL;
        }
        else
        {
            olist_ptr = olist_ptr->next_obj;
        }
        free ( temp_obj_ptr );
        return NULL;
    }
    else
    {
        prev_obj_ptr = olist_ptr;
        current_obj_ptr = olist_ptr->next_obj;

        while ( current_obj_ptr != NULL && current_obj_ptr->unum != obj_num )
        {
            prev_obj_ptr = current_obj_ptr;
            current_obj_ptr = current_obj_ptr->next_obj;
        }

        if ( current_obj_ptr != NULL )
        {
            temp_obj_ptr = current_obj_ptr;
            prev_obj_ptr->next_obj = current_obj_ptr->next_obj;
            free ( temp_obj_ptr );
            return olist_ptr;
        }
    }
    return NULL;
}

/* is a certain equipment type present? returns 1 or 0 */
int etype_present ( int type )
{
    int c;
    for ( c=0; c<7; c++ )
    {
        if ( equip[c].type == type )
        {
            return 1;
        }
    }
    return 0;
}

/* initialise weapons data */
void InitObjects()
{
    object weap;

    /* short-range weapons */
    weap.name = "forceknife";
    weap.unum = 0;
    weap.weight = 2;
    weap.type = SRW;
    weap.look = ')';
    weap.color = CYAN;
    weap.base_num = 1;
    weap.base_sides = 4;
    weap.to_dmg = 0;
    weap.to_hit = 0;
    srw[0] = weap;

    weap.name = "viral taser";
    weap.unum = 1;
    weap.weight = 2;
    weap.type = SRW;
    weap.look = ')';
    weap.color = GREEN;
    weap.base_num = 1;
    weap.base_sides = 5;
    weap.to_dmg = 0;
    weap.to_hit = 0;
    srw[1] = weap;

    weap.name = "telescopic baton";
    weap.unum = 2;
    weap.weight = 2;
    weap.type = SRW;
    weap.look = ')';
    weap.color = D_GREY;
    weap.base_num = 2;
    weap.base_sides = 3;
    weap.to_dmg = 0;
    weap.to_hit = 0;
    srw[2] = weap;

    /* long-range weapons */
    weap.name = "sharplight projector";
    weap.unum = 0;
    weap.weight = 3;
    weap.type = LRW;
    weap.look = ')';
    weap.color = RED;
    weap.base_num = 1;
    weap.base_range = 5;
    weap.base_sides = 6;
    weap.to_dmg = 0;
    weap.to_hit = 0;
    lrw[0] = weap;

    weap.name = "assault rifle";
    weap.unum = 1;
    weap.weight = 4;
    weap.type = LRW;
    weap.look = ')';
    weap.color = D_GREY;
    weap.base_num = 2;
    weap.base_range = 8;
    weap.base_sides = 6;
    weap.to_dmg = 0;
    weap.to_hit = 0;
    lrw[1] = weap;
}

/* generate starting equipment */
void gen_sinv ( int world, int regiment )
{
    if ( world == EAR )
    {
        equip[SRW] = srw[0];
        equip[LRW] = lrw[1];
    }
    if ( world == NEW )
    {
        equip[SRW] = srw[1];
        equip[LRW] = lrw[0];
    }
    if ( world == SPA )
    {
        equip[SRW] = srw[0];
        equip[LRW] = lrw[0];
    }
}

/* show inventory screen; return to main screen */
void show_inventory()
{
    int item_c = 0;
    int equip_present[7] = {0};
    object *prev_obj_ptr, *current_obj_ptr;

    TerminalClear();
    write_string ( 0,0,">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>",ColorFromName("blue") );
    write_string ( 0,35,"INVENTORY",ColorFromName("red") );
    write_string ( 0,44,"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<",ColorFromName("blue") );

    /* go through, print each item, then increment 'item_c'
       so you know where to start the next line */
    if ( etype_present ( SRW ) )
    {
        write_string ( 2,1,"Melee Weapons",ColorFromName("white") );
        write_string ( 3,1,"-------------",ColorFromName("white") );

        equip_present[SRW] = 1;
        item_c++;

        write_string ( 3+item_c,1,equip[SRW].name,ColorFromName("red") );
    }
    current_obj_ptr = inventory;
    if ( inventory !=  NULL )
    {
        if ( inventory->type == SRW )
        {
            if ( equip_present[SRW] != 1 )
            {
                write_string ( 2,1,"Melee Weapons",ColorFromName("white") );
                write_string ( 3,1,"-------------",ColorFromName("white") );
            }
            item_c++;
            write_string ( 3+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
        }
        else
        {
            prev_obj_ptr = inventory;
            current_obj_ptr = inventory->next_obj;

            while ( current_obj_ptr != NULL && current_obj_ptr->type != SRW )
            {
                prev_obj_ptr = inventory;
                current_obj_ptr = inventory->next_obj;
            }
            if ( current_obj_ptr != NULL )
            {
                if ( equip_present[SRW] != 1 )
                {
                    write_string ( 2,1,"Melee Weapons",ColorFromName("white") );
                    write_string ( 3,1,"-------------",ColorFromName("white") );
                }
                item_c++;
                write_string ( 3+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
            }
        }
    }

    if ( etype_present ( LRW ) )
    {
        write_string ( 5+item_c,1,"Ranged Weapons",ColorFromName("white") );
        write_string ( 6+item_c,1,"--------------",ColorFromName("white") );
        write_string ( 7+item_c,1,equip[LRW].name,ColorFromName("red") );
        item_c++;
    }
    if ( current_obj_ptr !=  NULL )
    {
        current_obj_ptr = inventory;
        if ( inventory->type == LRW )
        {
            if ( equip_present[LRW] != 1 )
            {
                write_string ( 5,1,"Ranged Weapons",ColorFromName("white") );
                write_string ( 6,1,"-------------",ColorFromName("white") );
            }
            item_c++;
            write_string ( 6+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
        }
        else
        {
            prev_obj_ptr = inventory;
            current_obj_ptr = inventory->next_obj;

            while ( current_obj_ptr != NULL && current_obj_ptr->type != LRW )
            {
                prev_obj_ptr = inventory;
                current_obj_ptr = inventory->next_obj;
            }
            if ( current_obj_ptr != NULL )
            {
                if ( equip_present[SRW] != 1 )
                {
                    write_string ( 5,1,"Ranged Weapons",ColorFromName("white") );
                    write_string ( 6,1,"-------------",ColorFromName("white") );
                }
                item_c++;
                write_string ( 6+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
            }
        }
    }

    if ( etype_present ( ARM ) )
    {
        write_string ( 8+item_c,1,"Armour",ColorFromName("white") );
        write_string ( 9+item_c,1,"------",ColorFromName("white") );
        write_string ( 10+item_c,1,equip[ARM].name,ColorFromName("red") );
        item_c++;
    }
    if ( current_obj_ptr !=  NULL )
    {
        current_obj_ptr = inventory;
        if ( inventory->type == LRW )
        {
            if ( equip_present[LRW] != 1 )
            {
                write_string ( 8,1,"Armour",ColorFromName("white") );
                write_string ( 9,1,"------",ColorFromName("white") );
            }
            item_c++;
            write_string ( 9+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
        }
        else
        {
            prev_obj_ptr = inventory;
            current_obj_ptr = inventory->next_obj;

            while ( current_obj_ptr != NULL && current_obj_ptr->type != LRW )
            {
                prev_obj_ptr = inventory;
                current_obj_ptr = inventory->next_obj;
            }
            if ( current_obj_ptr != NULL )
            {
                if ( equip_present[SRW] != 1 )
                {
                    write_string ( 8,1,"Armour",ColorFromName("white") );
                    write_string ( 9,1,"------",ColorFromName("white") );
                }
                item_c++;
                write_string ( 9+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
            }
        }
    }

    if ( etype_present ( HDA ) )
    {
        write_string ( 11+item_c,1,"Headgear",ColorFromName("white") );
        write_string ( 12+item_c,1,"--------",ColorFromName("white") );
        write_string ( 13+item_c,1,equip[HDA].name,ColorFromName("red") );
        item_c++;
    }
    if ( current_obj_ptr !=  NULL )
    {
        current_obj_ptr = inventory;
        if ( inventory->type == LRW )
        {
            if ( equip_present[LRW] != 1 )
            {
                write_string ( 11,1,"Headgear",ColorFromName("white") );
                write_string ( 12,1,"--------",ColorFromName("white") );
            }
            item_c++;
            write_string ( 12+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
        }
        else
        {
            prev_obj_ptr = inventory;
            current_obj_ptr = inventory->next_obj;

            while ( current_obj_ptr != NULL && current_obj_ptr->type != LRW )
            {
                prev_obj_ptr = inventory;
                current_obj_ptr = inventory->next_obj;
            }
            if ( current_obj_ptr != NULL )
            {
                if ( equip_present[SRW] != 1 )
                {
                    write_string ( 11,1,"Headgear",ColorFromName("white") );
                    write_string ( 12,1,"--------",ColorFromName("white") );
                }
                item_c++;
                write_string ( 12+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
            }
        }
    }

    if ( etype_present ( LGA ) )
    {
        write_string ( 14+item_c,1,"Legwear",ColorFromName("white") );
        write_string ( 15+item_c,1,"-------",ColorFromName("white") );
        write_string ( 16+item_c,1,equip[LGA].name,ColorFromName("red") );
        item_c++;
    }
    if ( current_obj_ptr !=  NULL )
    {
        current_obj_ptr = inventory;
        if ( inventory->type == LRW )
        {
            if ( equip_present[LRW] != 1 )
            {
                write_string ( 14,1,"Legwear",ColorFromName("white") );
                write_string ( 15,1,"-------",ColorFromName("white") );
            }
            item_c++;
            write_string ( 15+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
        }
        else
        {
            prev_obj_ptr = inventory;
            current_obj_ptr = inventory->next_obj;

            while ( current_obj_ptr != NULL && current_obj_ptr->type != LRW )
            {
                prev_obj_ptr = inventory;
                current_obj_ptr = inventory->next_obj;
            }
            if ( current_obj_ptr != NULL )
            {
                if ( equip_present[SRW] != 1 )
                {
                    write_string ( 14,1,"Legwear",ColorFromName("white") );
                    write_string ( 15,1,"-------",ColorFromName("white") );
                }
                item_c++;
                write_string ( 15+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
            }
        }
    }

    if ( etype_present ( FTA ) )
    {
        write_string ( 17+item_c,1,"Footwear",ColorFromName("white") );
        write_string ( 18+item_c,1,"--------",ColorFromName("white") );
        write_string ( 19+item_c,1,equip[FTA].name,ColorFromName("red") );
        item_c++;
    }
    if ( current_obj_ptr !=  NULL )
    {
        current_obj_ptr = inventory;
        if ( inventory->type == LRW )
        {
            if ( equip_present[LRW] != 1 )
            {
                write_string ( 17,1,"Footwear",ColorFromName("white") );
                write_string ( 18,1,"--------",ColorFromName("white") );
            }
            item_c++;
            write_string ( 18+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
        }
        else
        {
            prev_obj_ptr = inventory;
            current_obj_ptr = inventory->next_obj;

            while ( current_obj_ptr != NULL && current_obj_ptr->type != LRW )
            {
                prev_obj_ptr = inventory;
                current_obj_ptr = inventory->next_obj;
            }
            if ( current_obj_ptr != NULL )
            {
                if ( equip_present[SRW] != 1 )
                {
                    write_string ( 17,1,"Footwear",ColorFromName("white") );
                    write_string ( 18,1,"--------",ColorFromName("white") );
                }
                item_c++;
                write_string ( 18+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
            }
        }
    }

    if ( etype_present ( AMM ) )
    {
        write_string ( 20+item_c,1,"Ammunition",ColorFromName("white") );
        write_string ( 21+item_c,1,"----------",ColorFromName("white") );
        write_string ( 22+item_c,1,equip[AMM].name,ColorFromName("red") );
        item_c++;
    }
    if ( current_obj_ptr !=  NULL )
    {
        current_obj_ptr = inventory;
        if ( inventory->type == LRW )
        {
            if ( equip_present[LRW] != 1 )
            {
                write_string ( 20,1,"Ammunition",ColorFromName("white") );
                write_string ( 21,1,"----------",ColorFromName("white") );
            }
            item_c++;
            write_string ( 21+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
        }
        else
        {
            prev_obj_ptr = inventory;
            current_obj_ptr = inventory->next_obj;

            while ( current_obj_ptr != NULL && current_obj_ptr->type != LRW )
            {
                prev_obj_ptr = inventory;
                current_obj_ptr = inventory->next_obj;
            }
            if ( current_obj_ptr != NULL )
            {
                if ( equip_present[SRW] != 1 )
                {
                    write_string ( 20,1,"Armmunition",ColorFromName("white") );
                    write_string ( 21,1,"-----------",ColorFromName("white") );
                }
                item_c++;
                write_string ( 21+item_c,1,current_obj_ptr->name,ColorFromName("cyan") );
            }
        }
    }

    for ( ;; )
    {
        int c = TerminalRead();
        if ( c == TK_B )
        {
            break;
        }
    }

    ShowMainScreen( );
}

/* gets unum from location*/
int get_unum ( object *olist_ptr, int x, int y )
{
    object *prev_obj_ptr, *current_obj_ptr;

    if ( x == olist_ptr->xloc && y == olist_ptr->yloc )
    {
        return olist_ptr->unum;
    }
    else
    {
        prev_obj_ptr = olist_ptr;
        current_obj_ptr = olist_ptr->next_obj;

        while ( current_obj_ptr != NULL && current_obj_ptr->xloc != x && current_obj_ptr->yloc != y )
        {
            prev_obj_ptr = current_obj_ptr;
            current_obj_ptr = current_obj_ptr->next_obj;
        }
        if ( current_obj_ptr != NULL )
        {
            return current_obj_ptr->unum;
        }
    }
    return -1;
}

int get_color ( object *olist_ptr, int unum )
{
    object *prev_obj_ptr, *current_obj_ptr;

    if ( unum == olist_ptr->unum )
    {
        return olist_ptr->color;
    }
    else
    {
        prev_obj_ptr = olist_ptr;
        current_obj_ptr = olist_ptr->next_obj;

        while ( current_obj_ptr != NULL && current_obj_ptr->unum != unum )
        {
            prev_obj_ptr = current_obj_ptr;
            current_obj_ptr = current_obj_ptr->next_obj;
        }
        if ( current_obj_ptr != NULL )
        {
            return current_obj_ptr->color;
        }
    }
    return -1;
}

char get_look ( object *olist_ptr, int unum )
{
    object *prev_obj_ptr, *current_obj_ptr;

    if ( unum == olist_ptr->unum )
    {
        return olist_ptr->look;
    }
    else
    {
        prev_obj_ptr = olist_ptr;
        current_obj_ptr = olist_ptr->next_obj;

        while ( current_obj_ptr != NULL && current_obj_ptr->unum != unum )
        {
            prev_obj_ptr = current_obj_ptr;
            current_obj_ptr = current_obj_ptr->next_obj;
        }
        if ( current_obj_ptr != NULL )
        {
            return current_obj_ptr->look;
        }
    }
    return '\0';
}

/* returns -1 if failed */
int get_xloc ( object *olist_ptr, int unum )
{
    object *prev_obj_ptr, *current_obj_ptr;

    if ( unum == olist_ptr->unum )
    {
        return olist_ptr->xloc;
    }
    else
    {
        prev_obj_ptr = olist_ptr;
        current_obj_ptr = olist_ptr->next_obj;

        while ( current_obj_ptr != NULL && current_obj_ptr->unum != unum )
        {
            prev_obj_ptr = current_obj_ptr;
            current_obj_ptr = current_obj_ptr->next_obj;
        }
        if ( current_obj_ptr != NULL )
        {
            return current_obj_ptr->xloc;
        }
    }
    return -1;
}

int get_yloc ( object *olist_ptr, int unum )
{
    object *prev_obj_ptr, *current_obj_ptr;

    if ( unum == olist_ptr->unum )
    {
        return olist_ptr->yloc;
    }
    else
    {
        prev_obj_ptr = olist_ptr;
        current_obj_ptr = olist_ptr->next_obj;

        while ( current_obj_ptr != NULL && current_obj_ptr->unum != unum )
        {
            prev_obj_ptr = current_obj_ptr;
            current_obj_ptr = current_obj_ptr->next_obj;
        }
        if ( current_obj_ptr != NULL )
        {
            return current_obj_ptr->yloc;
        }
    }
    return -1;
}

char *get_oname ( object *olist_ptr, int unum )
{
    object *prev_obj_ptr, *current_obj_ptr;

    if ( unum == olist_ptr->unum )
    {
        return olist_ptr->name;
    }
    else
    {
        prev_obj_ptr = olist_ptr;
        current_obj_ptr = olist_ptr->next_obj;

        while ( current_obj_ptr != NULL && current_obj_ptr->unum != unum )
        {
            prev_obj_ptr = current_obj_ptr;
            current_obj_ptr = current_obj_ptr->next_obj;
        }
        if ( current_obj_ptr != NULL )
        {
            return current_obj_ptr->name;
        }
    }
    return NULL;
}


/* gets number of objects in a list */
int object_number ( object *olist )
{

    object *current_obj_ptr;
    int num_objects = 0;

    if ( olist == NULL )
    {
        return num_objects;
    }
    else
    {
        num_objects++;
        current_obj_ptr = olist;
    }

    while ( current_obj_ptr->next_obj != NULL )
    {
        current_obj_ptr = current_obj_ptr->next_obj;
        num_objects++;
    }

    return num_objects;
}


/*
 * tells whether an object is present at a location
 *  -returns object's unum, or NULL
 */
int object_present ( object *olist_ptr,  int x, int y )
{
    object *prev_obj_ptr, *current_obj_ptr;

    if ( olist_ptr == NULL )
    {
        return -1;
    }

    if ( x == olist_ptr->xloc && y == olist_ptr->yloc )
    {
        return olist_ptr->unum;
    }
    else
    {
        prev_obj_ptr = olist_ptr;
        current_obj_ptr = olist_ptr->next_obj;

        while ( current_obj_ptr != NULL && ( current_obj_ptr->xloc != x || current_obj_ptr->yloc != y ) )
        {
            prev_obj_ptr = current_obj_ptr;
            current_obj_ptr = current_obj_ptr->next_obj;
        }
        if ( current_obj_ptr != NULL )
        {
            return current_obj_ptr->unum;
        }
    }
    return -1;
}
