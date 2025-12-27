#include "./tetris_game.h"

#include "./defines_tetris.h"

int main() {
  WIN_INIT(5)
  srand(time(NULL));
  OG_timer_t graphic_timer, game_logic_timer;
  OG_timer_init(&graphic_timer, 0, 33000000);
  OG_timer_init(&game_logic_timer, 0, 10000000);
  ExtGameInfo_t* ExtendedGameObject = ExtendedGameObjectInitialization();
  print_game_start();

  while (ExtendedGameObject->state != EXIT_STATE) {
    if (check_timer_for_loops(&game_logic_timer) == 'y') {
      ExtendedGameObject->action = get_signal(getch());
      userInput((int)ExtendedGameObject->action,
                ExtendedGameObject->control_button_hold);
    }
    if (check_timer_for_loops(&graphic_timer) == 'y' &&
        (int)ExtendedGameObject->screen_changed) {
      print_game();
      if (ExtendedGameObject->show_controls_keys == TRUE) print_controls_keys();
      ExtendedGameObject->screen_changed = 0;
      // ExtendedGameObject->GameInfo->score += 1;
    }
  }

  GameFieldCleanup(ExtendedGameObject->GameInfo, BOARD_Y);

  endwin();

  return 0;
}
