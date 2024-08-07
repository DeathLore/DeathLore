#ifndef CLI_FRONT_H
#define CLI_FRONT_H

#include <ncurses.h>

#ifdef TETRIS
#include "../../brick_game/tetris/defines_tetris.h"
#else
#include "../../brick_game/tetris/defines_tetris.h"
#endif

#include "../../brick_game/backend/brick_backend.h"

/**
 * @brief Initializing game's screen (window) with ncurses lib.
 */
#define WIN_INIT(time)                        \
  {                                           \
    initscr();                                \
    noecho();                                 \
    curs_set(0);                              \
    keypad(stdscr, TRUE);                     \
    nodelay(stdscr, TRUE);                    \
    timeout(time);                            \
    start_color();                            \
    init_pair(0, COLOR_BLACK, COLOR_BLACK);   \
    init_pair(1, COLOR_RED, COLOR_BLACK);     \
    init_pair(2, COLOR_GREEN, COLOR_BLACK);   \
    init_pair(3, COLOR_BLUE, COLOR_BLACK);    \
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK); \
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);  \
  }

/**
 * @brief Prints string at some screen coordinates.
 */
#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)

/// @brief Adds character at some screen coordinates.
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

#define FRONT_BOARD_X (BOARD_X * 2)
#define FRONT_BOARD_Y (BOARD_Y)

/**
 * @brief (sub) Print func. that prints main game's overlay.
 *
 * @param[in] print_level is level used in this game.
 * @param[in] print_score is score used.
 * @param[in] print_best_score is high score used in game.
 * @param[in] print_speed is speed used.
 * @param[in] print_lives is lives used.
 */
void print_overlay(bool print_level, bool print_score, bool print_best_score,
                   bool print_speed, bool print_lives);

/**
 * @brief Prints error if failed to load levels. (currently unused)
 */
void print_level_error();

/**
 * @brief Prints rectangle at screen with ncurses library.
 *
 * @param top_y top Y rectangle's coordinate.
 * @param bottom_y bottom Y rectangle's coordinate.
 * @param left_x most left X rectangle's coordinate.
 * @param right_x most right X rectangle's coordinate.
 */
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
#endif