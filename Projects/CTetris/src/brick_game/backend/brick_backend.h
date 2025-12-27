#ifndef BRICK_BACKEND_H
#define BRICK_BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// Includes stat(); used to create folder and file inside it.
#include <sys/stat.h>

#include "./OG_timer.h"

/**
 * @brief Keys that are used in the game
 */
typedef enum {
  NOSIG,
  Start,      //* Enter button
  Pause,      //* 'p' button (English)
  Terminate,  //* ESC button
  Left,
  Right,
  Up,
  Down,
  Action,  //* Space button
  USERACTION_SIZE
} UserAction_t;

typedef enum { TetrisGame, BrickGameSize } BrickGame_t;

/**
 * @brief Structure that keeps common information about game
 */
typedef struct {
  //* Game field where located all objects
  //* Max Y - 20
  //* Max X - 10
  //* Point (0, 0) is at upper left corner
  int** field;
  int** next;
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
GameInfo_t* getGameObject();

/**
 * @brief Get current state of GameInfo.
 *
 * @return GameInfo_t
 */
GameInfo_t updateCurrentState();

void GameFieldCleanup(GameInfo_t* GameObject, const int board_y);

/**
 * @brief Returns saved HighScore.
 * In case of problem with reading file returns '-1'.
 *
 * @return int - returns HighScore or error (-1).
 */
int readHighScoreInfo(BrickGame_t const ByGame);

/**
 * @brief Saving HighScore in '.gd' file inside 'games_data' folder.
 *
 * @param HighScore Game's HighScore that have to be saved.
 */
void saveHighScoreInfo(int HighScore, BrickGame_t const ByGame);

/**
 * @brief Creates '.gd' file inside folder 'games_data' to store HighScore info.
 * If folder doesn't exists - it would be created.
 */
void createHighScoreInfoStorage(BrickGame_t const ByGame);

#endif