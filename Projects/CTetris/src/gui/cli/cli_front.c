#include "cli_front.h"

void print_overlay(bool print_level, bool print_score, bool print_best_score,
                   bool print_speed, bool print_lives) {
  GameInfo_t stats = updateCurrentState();
  print_rectangle(0, FRONT_BOARD_Y + 1, 0, FRONT_BOARD_X + 1);

  int HUD_count =
      print_level + print_score + print_best_score + print_speed + print_lives;
  if (HUD_count > 0)
    print_rectangle(0, FRONT_BOARD_Y + 1, FRONT_BOARD_X + 2,
                    FRONT_BOARD_X + HUD_WIDTH + 3);

  if (print_level) {
    print_rectangle(1, 3, FRONT_BOARD_X + 3, FRONT_BOARD_X + HUD_WIDTH + 2);
    MVPRINTW(2, FRONT_BOARD_X + 5, "LEVEL:");
    MVPRINTW(2, FRONT_BOARD_X + 12, "%d", stats.level);
  }
  if (print_best_score) {
    print_rectangle(4, 7, FRONT_BOARD_X + 3, FRONT_BOARD_X + HUD_WIDTH + 2);
    MVPRINTW(5, FRONT_BOARD_X + 5, "HIGH SCORE:");
    MVPRINTW(6, FRONT_BOARD_X + 5, "%d", stats.high_score);
  }
  if (print_score) {
    print_rectangle(8, 10, FRONT_BOARD_X + 3, FRONT_BOARD_X + HUD_WIDTH + 2);
    MVPRINTW(9, FRONT_BOARD_X + 5, "SCORE:");
    MVPRINTW(9, FRONT_BOARD_X + 12, "%d", stats.score);
  }
  if (print_speed) {
    print_rectangle(11, 13, FRONT_BOARD_X + 3, FRONT_BOARD_X + HUD_WIDTH + 2);
    MVPRINTW(12, FRONT_BOARD_X + 5, "SPEED:");
    MVPRINTW(12, FRONT_BOARD_X + 12, "%d", stats.speed);
  }
  if (print_lives) {
    print_rectangle(14, 16, FRONT_BOARD_X + 3, FRONT_BOARD_X + HUD_WIDTH + 2);
    MVPRINTW(15, FRONT_BOARD_X + 5, "LIVES:");
    MVPRINTW(15, FRONT_BOARD_X + 12, "%d", stats.lives);
  }
}

void print_level_error() {
  clear();
  MVPRINTW(0, 0, "An error occurred opening level file!");
  MVPRINTW(2, 0, "Please check ./tests/ directory.");
  MVPRINTW(3, 0, "There should be 5 level files named level_(1-5).txt.");
  MVPRINTW(4, 0, "Also try to open the game nearby ./tests/ directory.");
  MVPRINTW(6, 0, "Press any key to exit.");
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}