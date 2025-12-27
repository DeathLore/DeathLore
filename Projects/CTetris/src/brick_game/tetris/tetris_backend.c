#include "./tetris_backend.h"

ExtGameInfo_t* getExtGameObject() {
  static ExtGameInfo_t ExtGameObject = {0};

  return &ExtGameObject;
}

ExtGameInfo_t updateExtCurrentState() { return *getExtGameObject(); }

ExtGameInfo_t* ExtendedGameObjectInitialization() {
  ExtGameInfo_t* InitializedObject = getExtGameObject();
  InitializedObject->GameInfo = getGameObject();
  InitializedObject->action = NOSIG;
  InitializedObject->previous_action = NOSIG;
  InitializedObject->control_button_hold = false;
  choose_tetris_figure(rand() % 7, &(InitializedObject->next_figure));
  InitializedObject->state = 0;
  InitializedObject->screen_changed = false;
  InitializedObject->show_controls_keys = false;

  GameObjectInitialization();

  changeDropTimer(InitializedObject);

  return InitializedObject;
}

void GameObjectInitialization() {
  GameInfo_t* InitializedObject = getGameObject();

  InitializedObject->score = 0;

  InitializedObject->field = (int**)calloc(BOARD_Y, sizeof(int*));
  for (int rows = 0; rows < BOARD_Y; ++rows)
    InitializedObject->field[rows] = (int*)calloc(BOARD_X, sizeof(int));

  int HighScore_buffer = 0;
#ifndef TESTING
  if ((HighScore_buffer = readHighScoreInfo(TetrisGame)) == -1) {
    createHighScoreInfoStorage(TetrisGame);
    HighScore_buffer = 0;
  }
#endif
  InitializedObject->high_score = HighScore_buffer;

  InitializedObject->level = 1;
  InitializedObject->speed = 0;
  InitializedObject->pause = false;
}

void figure_insertion(TetrisFigure_t* figure, int figure_field[4][2],
                      char color, tetris_figure_shapes_t block_type) {
  for (char block = 0; block < 4; ++block) {
    figure->blocks_position[(int)block][0] = figure_field[(int)block][0];
    figure->blocks_position[(int)block][1] = figure_field[(int)block][1];
  }
  figure->color = color;
  figure->block_type = block_type;
  figure->rotate_case = 0;
}

void choose_tetris_figure(char figure_number,
                          TetrisFigure_t* figure_to_change) {
  static int tetris_i_figure[4][2] = {{3, 0}, {4, 0}, {5, 0}, {6, 0}};
  static int tetris_j_figure[4][2] = {{3, 0}, {3, 1}, {4, 1}, {5, 1}};
  static int tetris_l_figure[4][2] = {{3, 1}, {4, 1}, {5, 1}, {5, 0}};
  static int tetris_o_figure[4][2] = {{4, 0}, {5, 0}, {4, 1}, {5, 1}};
  static int tetris_s_figure[4][2] = {{3, 1}, {4, 1}, {4, 0}, {5, 0}};
  static int tetris_z_figure[4][2] = {{3, 0}, {4, 0}, {4, 1}, {5, 1}};
  static int tetris_t_figure[4][2] = {{3, 1}, {4, 1}, {4, 0}, {5, 1}};

  switch (figure_number) {
    case i_block:
      figure_insertion(figure_to_change, tetris_i_figure, 1, i_block);
      break;

    case j_block:
      figure_insertion(figure_to_change, tetris_j_figure, 2, j_block);
      break;

    case l_block:
      figure_insertion(figure_to_change, tetris_l_figure, 2, l_block);
      break;

    case o_block:
      figure_insertion(figure_to_change, tetris_o_figure, 3, o_block);
      break;

    case s_block:
      figure_insertion(figure_to_change, tetris_s_figure, 4, s_block);
      break;

    case z_block:
      figure_insertion(figure_to_change, tetris_z_figure, 4, z_block);
      break;

    case t_block:
      figure_insertion(figure_to_change, tetris_t_figure, 5, t_block);
      break;

    default:
      figure_insertion(figure_to_change, tetris_i_figure, 1, i_block);
      break;
  }
}

void changeDropTimer(ExtGameInfo_t* GameObject) {
  if (GameObject->GameInfo->level == 1)
    OG_timer_init(&(GameObject->figure_drop_timer), 2, 0);
  else if (GameObject->GameInfo->level == 2)
    OG_timer_init(&(GameObject->figure_drop_timer), 1, 950000000);
  else if (GameObject->GameInfo->level == 3)
    OG_timer_init(&(GameObject->figure_drop_timer), 1, 900000000);
  else if (GameObject->GameInfo->level == 4)
    OG_timer_init(&(GameObject->figure_drop_timer), 1, 800000000);
  else if (GameObject->GameInfo->level == 5)
    OG_timer_init(&(GameObject->figure_drop_timer), 1, 650000000);
  else if (GameObject->GameInfo->level == 6)
    OG_timer_init(&(GameObject->figure_drop_timer), 1, 400000000);
  else if (GameObject->GameInfo->level == 7)
    OG_timer_init(&(GameObject->figure_drop_timer), 1, 200000000);
  else if (GameObject->GameInfo->level == 8)
    OG_timer_init(&(GameObject->figure_drop_timer), 1, 0);
  else if (GameObject->GameInfo->level == 9)
    OG_timer_init(&(GameObject->figure_drop_timer), 0, 800000000);
  else if (GameObject->GameInfo->level == 10)
    OG_timer_init(&(GameObject->figure_drop_timer), 0, 500000000);
}

int check_figure_position(TetrisFigure_t const* const figure_to_check) {
  int result = 1;

  GameInfo_t* GameObject = getGameObject();

  int filled = 0;
  for (char block = 0; block < 4 && filled == 0; ++block) {
    if (figure_to_check->blocks_position[(int)block][1] >= 20)
      filled = 1;
    else if (figure_to_check->blocks_position[(int)block][0] < 0 ||
             figure_to_check->blocks_position[(int)block][0] > 9)
      filled = 1;
    else if (figure_to_check->blocks_position[(int)block][1] < 0)
      continue;
    else
      filled =
          GameObject->field[figure_to_check->blocks_position[(int)block][1]]
                           [figure_to_check->blocks_position[(int)block][0]];
  }

  if (filled) result = 0;

  return result;
}

void copy_figure_pos(TetrisFigure_t* destination, TetrisFigure_t* source) {
  for (char block = 0; block < 4; ++block) {
    destination->blocks_position[(int)block][0] =
        source->blocks_position[(int)block][0];
    destination->blocks_position[(int)block][1] =
        source->blocks_position[(int)block][1];
  }

  destination->rotate_case = source->rotate_case;
}