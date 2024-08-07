#ifndef FSM_H
#define FSM_H

#include "defines_tetris.h"
#include "tetris_frontend.h"

/**
 * @brief Tetris finite machine states
 *
 */
typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  PAUSE,
  GAMEOVER,
  EXIT_STATE,
  FILE_ERROR_STATE
} tetris_state;

/**
 * @brief Returns appropriate UserAction_t due to user's input.
 *
 * @param[in] user_input what user has entered (getch() as example)
 * @return char - UserAction_t
 */
char get_signal(int user_input);

/**
 * @brief Main FSM function that processes all states.
 *
 * @param action what action user do
 * @param hold
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Checks if new position of current figure is free
 *
 * @param y_shift what's the shift current figure have with Y coordinate to move
 * to a new position.
 * @param x_shift what's the shift current figure have with X coordinate to move
 * to a new position.
 * @return int - returns 'true' if new position isn't acceptable; if free -
 * 'false'.
 */
int check_collide(int y_shift, int x_shift);

#endif