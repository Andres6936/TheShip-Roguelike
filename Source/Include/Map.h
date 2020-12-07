#ifndef RT_MAP
#define RT_MAP 1

/* holds colors/characters for map-drawing */
typedef struct mapchar
{
    int unum;
    char symbol;
    int  color;
} mapchar;

// Dimension of dungeon (map).
extern const unsigned short DUNGEON_WIDTH;
extern const unsigned short DUNGEON_HEIGHT;

/* defines for map square types (mapchar struct) */
#define BLANK 0
#define WALL  1
#define FLR   2
#define UPSTR 3
#define DNSTR 4
#define CDOOR 5
#define ODOOR 6

void set_mapdrawing_chars();

void draw_lobjects();

void CreateDungeon( );

void print_map();

/* returns 1 if door is there, 0 otherwise */
int open_door();

/**
 * @brief Draw the dungeon (map) and the player.
 *
 * Clear the area of map only and next draw the dungeon (map) and player.
 * This method use the algorithm 'Scrolling Map' for draw the dungeon (map)
 * and center the player in the screen.
 * @note Require refresh the terminal for show to user.
 *
 * @pre Dungeon has been initialize.
 * @post Dungeon and player has been draw.
 */
void DrawDungeon( );

#endif
