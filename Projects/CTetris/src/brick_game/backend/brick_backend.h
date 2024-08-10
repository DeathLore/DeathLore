#ifndef BRICK_BACKEND_H
#define BRICK_BACKEND_H

#ifdef CLI
#include <ncurses.h>
#else
#include <ncurses.h>
#endif

#ifdef TETRIS
#include "../tetris/defines_tetris.h"
#else
#include "../tetris/defines_tetris.h"
#endif

#include <stdlib.h>

#include "OG_timer.h"

/**
 * @brief Keys that are used in the game
 */
typedef enum {
  Start,      //* Enter button
  Pause,      //* 'p' button (English)
  Terminate,  //* ESC button
  Left,
  Right,
  Up,
  Down,
  Action  //* Space button
} UserAction_t;

#define NOSIG 8

/**
 * @brief Structure that keeps common information about game
 */
typedef struct {
  //* Game field where located all objects
  //* Max Y - 20
  //* Max X - 10
  //* Point (0, 0) is at upper left corner
  int **field;
  int **next;
  //* Players Score
  int score;
  //* Best score player had
  int high_score;
  //* Current level
  int level;
  //* Game speed
  int speed;
  //* Is game paused or not
  int pause;
  //* How many lives left
  int lives;
} GameInfo_t;

/**
 * @brief Get the Game Object object.
 *
 * Also initialises GameInfo_t as static variable inside.
 *
 * @return GameInfo_t*
 */
GameInfo_t *getGameObject();

/**
 * @brief Get current state of GameInfo.
 *
 * @return GameInfo_t
 */
GameInfo_t updateCurrentState();

void deleteGameField(GameInfo_t *GameObject);

#endif