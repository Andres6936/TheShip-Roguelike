#ifndef RT_MAP
#define RT_MAP 1

/* holds colors/characters for map-drawing */
typedef struct mapchar
{
    int unum;
    char symbol;
    int  color;
} mapchar;

/* defines for map square types (mapchar struct) */
#define BLANK 0
#define WALL  1
#define FLR   2
#define UPSTR 3
#define DNSTR 4
#define CDOOR 5
#define ODOOR 6


enum Direction {N, NE, E, SE, S, SW, W, NW};

void set_mapdrawing_chars();

void draw_lobjects();

void init_screen_array();

void print_map();

/* returns 1 if door is there, 0 otherwise */
int open_door();

/*
 * draw the level features; current level
 * features are held in a global array
 */
void draw_lfeats();

#endif
