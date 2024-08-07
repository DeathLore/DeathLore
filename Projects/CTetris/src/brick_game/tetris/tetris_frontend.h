#ifndef TETRIS_FRONTEND_H
#define TETRIS_FRONTEND_H

#ifdef _cli
#include "../../gui/cli/cli_front.h"
/**
 * @brief (sub) Print func. that prints filed's content.
 */
#define PRINT_BOARD_POINT(color, y, x, character) \
  {                                               \
    attron(COLOR_PAIR(color));                    \
    MVADDCH(y + 1, x + 1, character);             \
    attroff(COLOR_PAIR(color));                   \
  }
#else
#include "../../gui/cli/cli_front.h"
/**
 * @brief (sub) Print func. that prints filed's content.
 */
#define PRINT_BOARD_POINT(color, y, x, character) \
  {                                               \
    attron(COLOR_PAIR(color));                    \
    MVADDCH(y + 1, x + 1, character);             \
    attroff(COLOR_PAIR(color));                   \
  }
#endif

#include "tetris_backend.h"

/**
 * @brief Game's main printing function.
 */
void print_game();
/**
 * @brief Function that prints initial screen when program started.
 */
void print_game_start();
/**
 * @brief Prints gameover screen.
 */
void print_gameover();
/**
 * @brief (sub) Print function that prints game's field.
 */
void print_board();
/**
 * @brief (sub) Print func. that prints next tetris figure at screen.
 */
void print_next_block();
/**
 * @brief (sub) Print func. that provides additional information. (Currently
 * used only for debugging)
 */
void print_additions();
/**
 * @brief (sub) Print func. that shows clue about game's control buttons.
 */
void print_controls_keys();

/**
 * @brief (sub) Print func. that flushes screen in order to update it.
 */
void flush_print();

#endif