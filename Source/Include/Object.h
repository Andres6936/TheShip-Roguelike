#ifndef RT_OBJECT
#define RT_OBJECT 1

typedef struct object
{
    struct object *next_obj;
    int unum;

    /* common attributes */
    char *name;
    int weight;
    int type;
    int color; /* color when on floor */
    int xloc; /* x,y location when on floor */
    int yloc;
    char look; /* symbol to represent object */

    /* weapon stats */
    int base_range;
    int base_num;
    int base_sides;
    int to_dmg;
    int to_hit;

} object;

/* 'type' defines */
#define SRW 0
#define LRW 1
#define ARM 2
#define HDA 3
#define LGA 4
#define FTA 5
#define AMM 6

/* linked list stuff */

object *insert_obj ( object *olist_ptr, object *obj_ptr );

object *delete_obj ( object *olist_ptr, int obj_num );

int etype_present ( int type );

int object_present ( object *olist_ptr, int x, int y );

void InitObjects();

void gen_sinv ( int _class, int gang );

void show_inventory();

int get_unum ( object *olist_ptr, int x, int y );

int get_color ( object *olist_ptr, int unum );

char get_look ( object *olist_ptr, int unum );

int get_xloc ( object *olist_ptr, int unum );

int get_yloc ( object *olist_ptr, int unum );

char *get_oname ( object *olist_ptr, int unum );

int object_number ( object *olist );


#endif
