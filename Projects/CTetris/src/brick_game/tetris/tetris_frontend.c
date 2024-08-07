#include "tetris_frontend.h"

void print_debug_info() {
  ExtGameInfo_t const* const GameObject = getExtGameObject();
  MVPRINTW(2, FRONT_BOARD_X + HUD_WIDTH + 5, "State: %d",
           (int)GameObject->state);
  MVPRINTW(3, FRONT_BOARD_X + HUD_WIDTH + 5, "Coordinates: ");
  for (int block = 0, padding = 0; block < 4; ++block) {
    MVPRINTW(3, FRONT_BOARD_X + HUD_WIDTH + 5 + 13 + padding, "%d %d",
             GameObject->curent_figure.blocks_position[block][0],
             GameObject->curent_figure.blocks_position[block][1]);
    padding += 5;
  }
}

void print_additions() {
#ifdef DEBUG
  print_debug_info();
#endif
  ;
}

void print_game() {
  flush_print();
  print_overlay(TRUE, TRUE, TRUE, FALSE, FALSE);
  print_next_block();
  print_board();

  print_additions();

  refresh();
}

void print_controls_keys() {
  MVPRINTW(13, FRONT_BOARD_X + HUD_WIDTH + 5, "Controls >");
  MVPRINTW(14, FRONT_BOARD_X + HUD_WIDTH + 5, "_________");
  MVPRINTW(15, FRONT_BOARD_X + HUD_WIDTH + 5, "Arrows:");
  MVPRINTW(16, FRONT_BOARD_X + HUD_WIDTH + 5,
           "Left - move left; Right - move right;");
  MVPRINTW(17, FRONT_BOARD_X + HUD_WIDTH + 5, "Down - move down");
  MVPRINTW(18, FRONT_BOARD_X + HUD_WIDTH + 5, "_________");
  MVPRINTW(19, FRONT_BOARD_X + HUD_WIDTH + 5,
           "Enter - start; ESC - close game; Space - action (rotate);");
  MVPRINTW(20, FRONT_BOARD_X + HUD_WIDTH + 5,
           "'p' - pause; 'c' - show/hide controls keys");
}

void print_game_start() {
  print_overlay(FALSE, FALSE, TRUE, FALSE, FALSE);

  MVPRINTW(5, 5, "Press 'Start'");
  MVPRINTW(6, 4, "to play Tetris!");

  MVPRINTW(15, 7, "Press 'c'");
  MVPRINTW(16, 3, "to show controls.");

  print_additions();
  print_controls_keys();

  refresh();
}

void print_gameover() {
  print_overlay(TRUE, TRUE, TRUE, FALSE, FALSE);

  MVPRINTW(5, 7, "GAMEOVER");
  MVPRINTW(8, 5, "Press 'Start'");
  MVPRINTW(9, 4, "to start again!");

  print_additions();

  refresh();
}

void flush_print() {
  // Next figure
  for (int rows = 0; rows < 4; ++rows)
    for (int cols = 0; cols < 8; ++cols)
      PRINT_BOARD_POINT(COLOR_BLACK, 15 + rows, FRONT_BOARD_X + 3 + cols, ' ');

  MVPRINTW(2, FRONT_BOARD_X + 12, "   ");      // Level
  MVPRINTW(6, FRONT_BOARD_X + 5, "        ");  // High Score
  MVPRINTW(9, FRONT_BOARD_X + 12, "       ");  // Score

  // Additional info and controls
  for (int rows = 2; rows <= BOARD_Y; ++rows)
    for (int cols = 0; cols < 17; ++cols) {                       // 16  57
      MVPRINTW(rows, FRONT_BOARD_X + HUD_WIDTH + 4 + cols, " ");  // Level
      if (rows == 5) rows = 13;
      if (rows == 3 || rows == 16 || rows == 19 || rows == 20) {
        MVPRINTW(rows, FRONT_BOARD_X + HUD_WIDTH + 5,
                 "                                                         ");
        continue;
      }
    }
}

void print_next_block() {
  MVPRINTW(13, FRONT_BOARD_X + 4, "NEXT FIGURE:");
  print_rectangle(14, 19, FRONT_BOARD_X + 3, FRONT_BOARD_X + 3 + 9);

  ExtGameInfo_t const* const GameObject = getExtGameObject();
  int color = (int)GameObject->next_figure.color;
  for (int block = 0; block < 4; ++block) {
    int CurrentXPosition =
            GameObject->next_figure.blocks_position[block][0] - 3,
        CurrentYPosition = GameObject->next_figure.blocks_position[block][1];
    int printed_column = CurrentXPosition * 2;

    PRINT_BOARD_POINT(color, 15 + CurrentYPosition,
                      FRONT_BOARD_X + 3 + printed_column, '[');
    PRINT_BOARD_POINT(color, 15 + CurrentYPosition,
                      FRONT_BOARD_X + 4 + printed_column, ']');
  }
}

void print_board() {
  const ExtGameInfo_t* GameObject = getExtGameObject();

  for (int line = 0, color = 0; line < BOARD_Y; ++line) {
    for (int column = 0, printed_column = 0, block_placed = 0; column < BOARD_X;
         ++column) {
      block_placed = 0;
      for (int block = 0; block < 4; ++block)
        if (GameObject->curent_figure.blocks_position[block][0] == column &&
            GameObject->curent_figure.blocks_position[block][1] == line) {
          color = (int)GameObject->curent_figure.color;
          PRINT_BOARD_POINT(color, line, printed_column++, '[')
          PRINT_BOARD_POINT(color, line, printed_column++, ']')
          block_placed = 1;
        }

      if ((color = GameObject->GameInfo->field[line][column]) == 0 &&
          block_placed == 0) {
        PRINT_BOARD_POINT(color, line, printed_column++, ' ')
        PRINT_BOARD_POINT(color, line, printed_column++, ' ')
      } else if (block_placed == 0) {
        PRINT_BOARD_POINT(color, line, printed_column++, '[')
        PRINT_BOARD_POINT(color, line, printed_column++, ']')
      }
    }
  }
}