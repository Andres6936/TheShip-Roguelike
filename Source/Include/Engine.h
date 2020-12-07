// Include file only once
#pragma once

#include "BearLibTerminal/BearLibTerminal.hpp"

/* color defines */
#define RED     0
#define GREEN   1
#define CYAN    2
#define L_GREY  3
#define BROWN   4
#define BLUE    5
#define MAGENTA 6
#define BLACK   7
#define ORANGE  8
#define L_GREEN 9
#define L_CYAN  10
#define WHITE   11
#define YELLOW  12
#define L_BLUE  13
#define PINK    14
#define D_GREY  15

void InitEngine ( void );

void ExitApplication( short );

/**
 * @brief Write a character, 'c', to the co-ords (x,y) with colour 'color'.
 *
 * @param x: Coordinate in X.
 * @param y: Coordinate in Y.
 * @param c: Char to draw or write.
 * @param color: Color foreground of char.
 */
void WriteChar( int x, int y, char c, color_t color );

void write_string ( int x, int y, char *s, color_t color );
