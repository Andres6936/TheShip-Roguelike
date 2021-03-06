// Only include file once
#pragma once

extern const short VIEW_DUNGEON_WIDTH;
extern const short VIEW_DUNGEON_HEIGHT;

int ShowWorldChoice( );

int ShowRegimentChoice( );

void ShowTitleScreen( );

void ShowMainScreen( );

/**
 * @brief Draw the border line of user interface.
 *
 * @note This method assumes that BearLibTerminal uses encoding cp437,
 * it means that when calling the set method, it must have the following
 * parameter: "terminal: encoding = 437".
 *
 * @note This method assumes that size of terminal is 80x25 or more.
 *
 * @code In C99: TerminalSet("terminal: encoding=437")
 */
void ShowBorderLine();

void print_msg ( char *msg );
