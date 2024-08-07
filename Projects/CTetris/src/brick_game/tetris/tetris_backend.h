#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

// Includes stat(); used to create folder and file inside it.
#include <sys/stat.h>

#include "../backend/brick_backend.h"

/**
 * @brief Structure that represents figure on field.
 */
typedef struct {
  /**
   * @brief There are 4 blocks with 2 coordinates each.
   * [*][0] - X coordinate;
   * [*][1] - Y coordinate
   */
  int blocks_position[4][2];
  /// No means, used only to map colors in the frontend part.
  char color;
  /// Represents figure's shape.
  char block_type;
  /// How figure is rotated.
  char rotate_case;
} TetrisFigure_t;

/**
 * @brief Structure that keeps all necessary game information.
 */
typedef struct {
  /// @brief Pointer to basic game info.
  GameInfo_t* GameInfo;
  /// @brief What's current action made by user.
  char action;
  /// @brief Previous user's action (unused).
  char previous_action;
  /// @brief Does user holds some action (unused).
  bool control_button_hold;
  /// @brief Current tetris figure that user controls.
  TetrisFigure_t curent_figure;
  /// @brief Next figure that will replace the current one.
  TetrisFigure_t next_figure;
  /// @brief Finite machine's state.
  char state;
  /// @brief Flag that decides to print game again if something changed.
  char screen_changed;
  /// @brief Timer that causes current figure to move down automaticaly.
  OG_timer_t figure_drop_timer;
  /// @brief Flag that chooses to show or hide game's control buttons as clue.
  bool show_controls_keys;
} ExtGameInfo_t;

/**
 * @brief Enum-ting all tetris figure shapes.
 */
typedef enum {
  i_block = 0,
  j_block,
  l_block,
  o_block,
  s_block,
  t_block,
  z_block
} tetris_figure_shapes_t;

/**
 * @brief Get Extended Game Object.
 *
 * Also initialises GameInfo_t as static variable inside.
 *
 * @return ExtGameInfo_t*
 */
ExtGameInfo_t* getExtGameObject();

/**
 * @brief updates current state of ExtGameInfo.
 *
 * @return ExtGameInfo_t
 */
ExtGameInfo_t updateExtCurrentState();

/**
 * @brief Sets default values for game's info (extended part).
 *
 * @return ExtGameInfo_t* - returns new one ExtGameInfo's example.
 */
ExtGameInfo_t* ExtendedGameObjectInitialization();

/**
 * @brief Sets default values for game's info (basic part).
 */
void GameObjectInitialization();

/**
 * @brief Returns saved HighScore.
 * In case of problem with reading file returns '-1'.
 *
 * @return int - returns HighScore or error (-1).
 */
int readHighScoreInfo();

/**
 * @brief Saving HighScore in '.gd' file inside 'games_data' folder.
 *
 * @param HighScore Game's HighScore that have to be saved.
 */
void saveHighScoreInfo(int HighScore);

/**
 * @brief Creates '.gd' file inside folder 'games_data' to store HighScore info.
 * If folder doesn't exists - it would be created.
 */
void createHighScoreInfoStorage();

/**
 * @brief Choosing new tetris figure instead of previous.
 *
 * @param[in] figure_number - insert one of seven figure shapes
 * ('tetris_figure_shapes_t').
 * @param[in, out] figure_to_change - figure that would be transformed into new
 * one.
 */
void choose_tetris_figure(char figure_number, TetrisFigure_t* figure_to_change);

/**
 * @brief Checks if pointed figure could be placed in game field.
 *
 * @param[in] figure_to_check
 * @return int: 'true' - if figure could be place; else 'false'.
 */
int check_figure_position(TetrisFigure_t const* const figure_to_check);

/**
 * @brief Coping position and rotate data from source figure to destination
 * figure.
 *
 * @param destination
 * @param source
 */
void copy_figure_pos(TetrisFigure_t* destination, TetrisFigure_t* source);

/**
 * @brief Changing game's 'figure_drop_timer' variable due to game level.
 *
 * @param[in, out] GameObject
 */
void changeDropTimer(ExtGameInfo_t* GameObject);
#endif