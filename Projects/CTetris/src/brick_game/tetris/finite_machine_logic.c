#include "finite_machine_logic.h"

// This is a finite state machine realization based on matrix of "actions".

void collide_sequences();
int check_lines(ExtGameInfo_t *GameObject);
void move_field_after_check(GameInfo_t *GameObject, int affected_lines[4]);
void changeSpeedTimer(ExtGameInfo_t *GameObject);

typedef void (*fsm_action)(ExtGameInfo_t *prms);

void spawn(ExtGameInfo_t *prms);
void movedown(ExtGameInfo_t *prms);
void moveright(ExtGameInfo_t *prms);
void moveleft(ExtGameInfo_t *prms);
void gameover(ExtGameInfo_t *prms);
void exitstate(ExtGameInfo_t *prms);
void pause(ExtGameInfo_t *prms);
void rotate(ExtGameInfo_t *prms);
void unpause(ExtGameInfo_t *prms);

fsm_action fsm_table[7][9] = {
    {spawn, NULL, exitstate, NULL, NULL, NULL, NULL, NULL, NULL},
    {spawn, spawn, exitstate, spawn, spawn, spawn, spawn, spawn, spawn},
    {NULL, pause, exitstate, moveleft, moveright, NULL, movedown, rotate, NULL},
    {unpause, NULL, exitstate, NULL, NULL, NULL, NULL, NULL, NULL},
    {gameover, gameover, exitstate, gameover, gameover, gameover, gameover,
     gameover, gameover},
    {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate,
     exitstate, exitstate, exitstate}};

int rotate_i(TetrisFigure_t *curent_figure);
int rotate_j(TetrisFigure_t *curent_figure);
int rotate_l(TetrisFigure_t *curent_figure);
int rotate_s(TetrisFigure_t *curent_figure);
int rotate_t(TetrisFigure_t *curent_figure);
int rotate_z(TetrisFigure_t *curent_figure);

void userInput(UserAction_t action, bool hold) {
  ExtGameInfo_t *ExtGameObject = getExtGameObject();

  ExtGameObject->action = action;
  ExtGameObject->control_button_hold = hold;

  fsm_action act = NULL;

  if (action == (int)'c')
    ExtGameObject->show_controls_keys = !ExtGameObject->show_controls_keys;
  else if (ExtGameObject->state != FILE_ERROR_STATE) {
    if (action != Terminate && ExtGameObject->state == MOVING &&
        check_timer_for_loops(&(ExtGameObject->figure_drop_timer)) == 'y')
      act = movedown;
    else
      act = fsm_table[(int)ExtGameObject->state][action];
  }

  if (act) act(ExtGameObject);
}

char get_signal(int user_input) {
  char rc = NOSIG;
#ifdef DEBUG
  ExtGameInfo_t *GameObject = getExtGameObject();
#endif

  if (user_input == KEY_UP)
    rc = Up;
  else if (user_input == KEY_DOWN)
    rc = Down;
  else if (user_input == KEY_LEFT)
    rc = Left;
  else if (user_input == KEY_RIGHT)
    rc = Right;
  else if (user_input == LOCAL_KEY_ESCAPE)
    rc = Terminate;
  else if (user_input == ' ')
    rc = Action;
  else if (user_input == 'p')
    rc = Pause;
  else if (user_input == LOCAL_KEY_ENTER)
    rc = Start;
  else if (user_input == 'c')
    rc = 'c';
#ifdef DEBUG
  else if (user_input == 'l') {
    GameObject->GameInfo->level += 1;
    GameObject->GameInfo->score += 600;
    changeDropTimer(GameObject);
  } else if (user_input == 's')
    GameObject->state += 1;
#endif

  return rc;
}

void spawn(ExtGameInfo_t *prms) {
  prms->curent_figure.block_type = prms->next_figure.block_type;
  for (int block = 0; block < 4; ++block) {
    prms->curent_figure.blocks_position[block][0] =
        prms->next_figure.blocks_position[block][0];
    prms->curent_figure.blocks_position[block][1] =
        prms->next_figure.blocks_position[block][1];
  }
  prms->curent_figure.color = prms->next_figure.color;
  prms->curent_figure.rotate_case = 0;
  choose_tetris_figure((rand() + 1 / rand()) % 7, &(prms->next_figure));
  prms->screen_changed = TRUE;

  if (check_collide(0, 0) == TRUE) {
    prms->state = GAMEOVER;
  } else
    prms->state = MOVING;
}

int check_collide(int y_shift, int x_shift) {
  int collided = FALSE;
  ExtGameInfo_t GameCheckObject = updateExtCurrentState();

  for (int block = 0; block < 4 && collided != TRUE; ++block) {
    int currentYPosition =
        GameCheckObject.curent_figure.blocks_position[block][1];
    int currentXPosition =
        GameCheckObject.curent_figure.blocks_position[block][0];
    if (currentYPosition == BOARD_Y - 1 || currentXPosition + x_shift < 0)
      collided = TRUE;
    else if (currentYPosition < 0)
      continue;
    else if (GameCheckObject.GameInfo->field[currentYPosition + y_shift]
                                            [currentXPosition + x_shift] != 0)
      collided = TRUE;
  }

  return collided;
}

void movedown(ExtGameInfo_t *prms) {
  if (check_collide(1, 0)) {
    prms->state = SPAWN;

    for (int block = 0; block < 4; ++block) {
      prms->GameInfo->field[prms->curent_figure.blocks_position[block][1]]
                           [prms->curent_figure.blocks_position[block][0]] =
          prms->curent_figure.color;
    }

    collide_sequences();
  } else {
    for (int block = 0; block < 4; ++block) {
      prms->curent_figure.blocks_position[block][1] += 1;
    }
  }

  prms->screen_changed = TRUE;
}

void collide_sequences() {
  ExtGameInfo_t *GameObject = getExtGameObject();
  int lines_filled = check_lines(GameObject);

  if (lines_filled == 1) {
    GameObject->GameInfo->score += 100;
  } else if (lines_filled == 2) {
    GameObject->GameInfo->score += 300;
  } else if (lines_filled == 3) {
    GameObject->GameInfo->score += 700;
  } else if (lines_filled == 4) {
    GameObject->GameInfo->score += 1500;
  }

  int score_to_level = GameObject->GameInfo->score / 600 + 1;
  if (score_to_level < 11) {
    if (GameObject->GameInfo->level != score_to_level) {
      GameObject->GameInfo->level = score_to_level;

      changeDropTimer(GameObject);
    }
  }
}

int check_lines(ExtGameInfo_t *GameObject) {
  int lines_filled = 0;
  int affected_lines[4] = {0};

  for (int block = 0, line = 0; block < 4; ++block) {
    line = GameObject->curent_figure.blocks_position[block][1];

    for (int counter = 0; counter < 4; ++counter) {
      if (affected_lines[counter] == line)
        counter = 6;
      else if (affected_lines[counter] == 0) {
        affected_lines[counter] = line;
        counter = 6;
      }
    }
  }

  for (int line = 0; line < 4; ++line) {
    int filled = TRUE;
    for (int column = 0; column < BOARD_X && filled == TRUE; ++column) {
      if (GameObject->GameInfo->field[affected_lines[line]][column] == 0)
        filled = FALSE;
    }

    if (filled == TRUE)
      lines_filled += 1;
    else
      affected_lines[line] = 0;
  }

  move_field_after_check(GameObject->GameInfo, affected_lines);

  return lines_filled;
}

void move_field_after_check(GameInfo_t *GameObject, int affected_lines[4]) {
  for (int af_line_counter = 0; af_line_counter < 4; ++af_line_counter) {
    for (int rows = affected_lines[af_line_counter];
         rows >= 0 && affected_lines[af_line_counter] != 0; --rows)
      for (int cols = 0; cols < BOARD_X; ++cols) {
        if (rows > 0)
          GameObject->field[rows][cols] = GameObject->field[rows - 1][cols];
        else
          GameObject->field[rows][cols] = 0;
      }
  }
}

void moveright(ExtGameInfo_t *prms) {
  if (!check_collide(0, 1)) {
    for (int block = 0; block < 4; ++block) {
      prms->curent_figure.blocks_position[block][0] += 1;
      prms->screen_changed = TRUE;
    }
  }
}

void moveleft(ExtGameInfo_t *prms) {
  if (!check_collide(0, -1)) {
    for (int block = 0; block < 4; ++block) {
      prms->curent_figure.blocks_position[block][0] -= 1;
      prms->screen_changed = TRUE;
    }
  }
}

void gameover(ExtGameInfo_t *prms) {
  if (prms->GameInfo->high_score < prms->GameInfo->score)
    saveHighScoreInfo(prms->GameInfo->score);

  deleteGameField(prms->GameInfo);

#ifndef TESTING
  print_gameover();
#endif
  ExtendedGameObjectInitialization();
}

void exitstate(ExtGameInfo_t *prms) { prms->state = EXIT_STATE; }

// TO DO sub 'rotate_*' funcs
void rotate(ExtGameInfo_t *prms) {
  int should_screen_change = 0;
  switch (prms->curent_figure.block_type) {
    case i_block:
      should_screen_change = rotate_i(&prms->curent_figure);
      break;

    case j_block:
      should_screen_change = rotate_j(&prms->curent_figure);
      break;

    case l_block:
      should_screen_change = rotate_l(&prms->curent_figure);
      break;

    case o_block:
      should_screen_change = FALSE;
      break;

    case s_block:
      should_screen_change = rotate_s(&prms->curent_figure);
      break;

    case t_block:
      should_screen_change = rotate_t(&prms->curent_figure);
      break;

    case z_block:
      should_screen_change = rotate_z(&prms->curent_figure);
      break;
  }

  prms->screen_changed = should_screen_change;
}

int rotate_i(TetrisFigure_t *curent_figure) {
  int rotated = 0;
  TetrisFigure_t fig_buffer = {0};
  if (curent_figure->rotate_case == 0) {
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] + 1;
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] - 1;
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] - 1;
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] + 1;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] - 2;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] + 2;

    fig_buffer.rotate_case = 1;
  } else {
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] - 1;
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] + 1;
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] + 1;
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] - 1;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] + 2;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] - 2;

    fig_buffer.rotate_case = 0;
  }

  if (check_figure_position(&fig_buffer)) {
    copy_figure_pos(curent_figure, &fig_buffer);
    rotated = 1;
  }

  return rotated;
}

int rotate_j(TetrisFigure_t *curent_figure) {
  int rotated = 0;
  TetrisFigure_t fig_buffer = {0};

  if (curent_figure->rotate_case == 0) {
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] + 2;
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1];
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0] + 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1] - 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1];
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] - 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] + 1;

    fig_buffer.rotate_case = 1;
  } else if (curent_figure->rotate_case == 1) {
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0];
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] + 2;
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0] + 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1] + 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1];
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] - 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] - 1;

    fig_buffer.rotate_case = 2;
  } else if (curent_figure->rotate_case == 2) {
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] - 2;
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1];
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0] - 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1] + 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1];
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] + 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] - 1;

    fig_buffer.rotate_case = 3;
  } else {
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0];
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] - 2;
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0] - 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1] - 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1];
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] + 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] + 1;

    fig_buffer.rotate_case = 0;
  }

  if (check_figure_position(&fig_buffer)) {
    copy_figure_pos(curent_figure, &fig_buffer);
    rotated = 1;
  }

  return rotated;
}

int rotate_l(TetrisFigure_t *curent_figure) {
  int rotated = 0;
  TetrisFigure_t fig_buffer = {0};

  if (curent_figure->rotate_case == 0) {
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] + 1;
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] - 1;
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] - 1;
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] + 1;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0];
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] + 2;

    fig_buffer.rotate_case = 1;
  } else if (curent_figure->rotate_case == 1) {
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] + 1;
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] + 1;
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] - 1;
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] - 1;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] - 2;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1];

    fig_buffer.rotate_case = 2;
  } else if (curent_figure->rotate_case == 2) {
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] - 1;
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] + 1;
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] + 1;
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] - 1;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0];
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] - 2;

    fig_buffer.rotate_case = 3;
  } else {
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] - 1;
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] - 1;
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] + 1;
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] + 1;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] + 2;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1];

    fig_buffer.rotate_case = 0;
  }

  if (check_figure_position(&fig_buffer)) {
    copy_figure_pos(curent_figure, &fig_buffer);
    rotated = 1;
  }

  return rotated;
}

int rotate_s(TetrisFigure_t *curent_figure) {
  int rotated = 0;
  TetrisFigure_t fig_buffer = {0};

  if (curent_figure->rotate_case == 0) {
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] - 1;
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] + 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] + 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] + 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] + 2;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0];

    fig_buffer.rotate_case = 1;
  } else {
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] + 1;
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] - 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] - 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] - 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] - 2;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0];

    fig_buffer.rotate_case = 0;
  }

  if (check_figure_position(&fig_buffer)) {
    copy_figure_pos(curent_figure, &fig_buffer);
    rotated = 1;
  }

  return rotated;
}

int rotate_t(TetrisFigure_t *curent_figure) {
  int rotated = 0;
  TetrisFigure_t fig_buffer = {0};

  if (curent_figure->rotate_case == 0) {
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] - 1;
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] + 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] + 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] + 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] + 1;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] - 1;

    fig_buffer.rotate_case = 1;
  } else if (curent_figure->rotate_case == 1) {
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] + 1;
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] + 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] + 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] - 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] - 1;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] - 1;

    fig_buffer.rotate_case = 2;
  } else if (curent_figure->rotate_case == 2) {
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] + 1;
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] - 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] - 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] - 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] - 1;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] + 1;

    fig_buffer.rotate_case = 3;
  } else {
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] - 1;
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] - 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] - 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] + 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] + 1;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0] + 1;

    fig_buffer.rotate_case = 0;
  }

  if (check_figure_position(&fig_buffer)) {
    copy_figure_pos(curent_figure, &fig_buffer);
    rotated = 1;
  }

  return rotated;
}

int rotate_z(TetrisFigure_t *curent_figure) {
  int rotated = 0;
  TetrisFigure_t fig_buffer = {0};

  if (curent_figure->rotate_case == 0) {
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] + 1;
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] + 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] - 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] + 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] - 2;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0];

    fig_buffer.rotate_case = 1;
  } else {
    fig_buffer.blocks_position[0][1] = curent_figure->blocks_position[0][1] - 1;
    fig_buffer.blocks_position[0][0] = curent_figure->blocks_position[0][0] - 1;
    fig_buffer.blocks_position[1][1] = curent_figure->blocks_position[1][1];
    fig_buffer.blocks_position[1][0] = curent_figure->blocks_position[1][0];
    fig_buffer.blocks_position[2][1] = curent_figure->blocks_position[2][1] + 1;
    fig_buffer.blocks_position[2][0] = curent_figure->blocks_position[2][0] - 1;
    fig_buffer.blocks_position[3][1] = curent_figure->blocks_position[3][1] + 2;
    fig_buffer.blocks_position[3][0] = curent_figure->blocks_position[3][0];

    fig_buffer.rotate_case = 0;
  }

  if (check_figure_position(&fig_buffer)) {
    copy_figure_pos(curent_figure, &fig_buffer);
    rotated = 1;
  }

  return rotated;
}

void pause(ExtGameInfo_t *prms) {
  prms->state = PAUSE;
  prms->GameInfo->pause = TRUE;
#ifndef TESTING
  print_game();
  if (prms->show_controls_keys) print_controls_keys();
  MVPRINTW(7, 8, "PAUSE|>");
#endif
}

void unpause(ExtGameInfo_t *prms) {
  prms->state = MOVING;
  prms->GameInfo->pause = FALSE;
  check_timer_for_loops(&prms->figure_drop_timer);

  prms->screen_changed = TRUE;
}