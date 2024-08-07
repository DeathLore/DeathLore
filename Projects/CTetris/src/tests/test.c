#include <check.h>

#include "../brick_game/tetris/finite_machine_logic.h"

// START_TEST() {

// }
// END_TEST

START_TEST(get_GameInfo) {
  GameInfo_t* GameObj_init = getGameObject();
  GameObj_init->level = 3;

  GameInfo_t* GameObj_test = getGameObject();

  ck_assert_int_eq(GameObj_test->level, 3);
  ck_assert_int_eq(GameObj_test->lives, 0);
  ck_assert_int_eq(GameObj_test->pause, 0);
  ck_assert_int_eq(GameObj_test->speed, 0);
  ck_assert_int_eq(GameObj_test->high_score, 0);
  ck_assert_int_eq(GameObj_test->score, 0);
}
END_TEST

START_TEST(update_GameInfo) {
  GameInfo_t* GameObj_init = getGameObject();
  GameObj_init->lives = 5;

  GameInfo_t GameObj_test = updateCurrentState();

  ck_assert_int_eq(GameObj_test.level, 0);
  ck_assert_int_eq(GameObj_test.lives, 5);
  ck_assert_int_eq(GameObj_test.pause, 0);
  ck_assert_int_eq(GameObj_test.speed, 0);
  ck_assert_int_eq(GameObj_test.high_score, 0);
  ck_assert_int_eq(GameObj_test.score, 0);
}
END_TEST

START_TEST(get_ExtGameInfo) {
  ExtGameInfo_t* GameObj_init = getExtGameObject();
  GameObj_init->action = Pause;
  GameObj_init->state = GAMEOVER;

  ExtGameInfo_t* GameObj_test = getExtGameObject();

  ck_assert_int_eq((int)GameObj_test->action, Pause);
  ck_assert_int_eq((int)GameObj_test->previous_action, 0);
  ck_assert_int_eq(GameObj_test->control_button_hold, 0);
  ck_assert_int_eq((int)GameObj_test->state, GAMEOVER);
  ck_assert_int_eq((int)GameObj_test->screen_changed, 0);
  ck_assert_int_eq(GameObj_test->show_controls_keys, 0);
}
END_TEST

START_TEST(update_ExtGameInfo) {
  ExtGameInfo_t* GameObj_init = getExtGameObject();
  GameObj_init->action = Action;
  GameObj_init->state = MOVING;
  GameObj_init->screen_changed = TRUE;

  ExtGameInfo_t GameObj_test = updateExtCurrentState();

  ck_assert_int_eq((int)GameObj_test.action, Action);
  ck_assert_int_eq((int)GameObj_test.previous_action, 0);
  ck_assert_int_eq(GameObj_test.control_button_hold, 0);
  ck_assert_int_eq((int)GameObj_test.state, MOVING);
  ck_assert_int_eq((int)GameObj_test.screen_changed, TRUE);
  ck_assert_int_eq(GameObj_test.show_controls_keys, 0);
}
END_TEST

START_TEST(get_signals) {
  ck_assert_int_eq((int)get_signal('p'), Pause);
  ck_assert_int_eq((int)get_signal(KEY_UP), Up);
  ck_assert_int_eq((int)get_signal(KEY_DOWN), Down);
  ck_assert_int_eq((int)get_signal(KEY_LEFT), Left);
  ck_assert_int_eq((int)get_signal(KEY_RIGHT), Right);
  ck_assert_int_eq((int)get_signal(LOCAL_KEY_ENTER), Start);
  ck_assert_int_eq((int)get_signal(LOCAL_KEY_ESCAPE), Terminate);
  ck_assert_int_eq((int)get_signal(' '), Action);
  ck_assert_int_eq((int)get_signal('c'), (int)'c');
}
END_TEST

START_TEST(GameInit) {
  GameObjectInitialization();
  GameInfo_t GameObject = updateCurrentState();

  ck_assert_int_eq(GameObject.level, 1);
  ck_assert_int_eq(GameObject.lives, 0);
  ck_assert_int_eq(GameObject.pause, FALSE);
  ck_assert_int_eq(GameObject.speed, 0);
  ck_assert_int_eq(GameObject.high_score, 0);
  ck_assert_int_eq(GameObject.score, 0);
  ck_assert_int_eq(GameObject.field[5][6], 0);

  deleteGameField(&GameObject);
}
END_TEST

START_TEST(ExtGameInit) {
  ExtendedGameObjectInitialization();
  ExtGameInfo_t GameObject = updateExtCurrentState();

  ck_assert_int_eq(GameObject.figure_drop_timer.delay.tv_sec, 2);
  ck_assert_int_eq(GameObject.action, NOSIG);
  ck_assert_int_eq(GameObject.control_button_hold, FALSE);
  ck_assert_int_eq(GameObject.GameInfo->field[2][6], 0);
  ck_assert_int_ge(GameObject.next_figure.color, 1);
  ck_assert_int_eq(GameObject.previous_action, NOSIG);
  ck_assert_int_eq(GameObject.screen_changed, FALSE);
  ck_assert_int_eq(GameObject.show_controls_keys, FALSE);
  ck_assert_int_eq(GameObject.state, Start);

  deleteGameField(GameObject.GameInfo);
}
END_TEST

START_TEST(chooseFigure) {
  TetrisFigure_t Figure = {0};
  choose_tetris_figure(i_block, &Figure);
  ck_assert_int_eq((int)Figure.block_type, i_block);
  ck_assert_int_eq((int)Figure.color, 1);
  ck_assert_int_eq(Figure.blocks_position[0][0], 3);
  ck_assert_int_eq(Figure.blocks_position[0][1], 0);
  ck_assert_int_eq(Figure.blocks_position[1][0], 4);
  ck_assert_int_eq(Figure.blocks_position[1][1], 0);
  ck_assert_int_eq(Figure.blocks_position[2][0], 5);
  ck_assert_int_eq(Figure.blocks_position[2][1], 0);
  ck_assert_int_eq(Figure.blocks_position[3][0], 6);
  ck_assert_int_eq(Figure.blocks_position[3][1], 0);

  choose_tetris_figure(j_block, &Figure);
  ck_assert_int_eq((int)Figure.block_type, j_block);

  choose_tetris_figure(l_block, &Figure);
  ck_assert_int_eq((int)Figure.block_type, l_block);

  choose_tetris_figure(o_block, &Figure);
  ck_assert_int_eq((int)Figure.block_type, o_block);

  choose_tetris_figure(s_block, &Figure);
  ck_assert_int_eq((int)Figure.block_type, s_block);

  choose_tetris_figure(t_block, &Figure);
  ck_assert_int_eq((int)Figure.block_type, t_block);

  choose_tetris_figure(z_block, &Figure);
  ck_assert_int_eq((int)Figure.block_type, z_block);

  choose_tetris_figure(9, &Figure);
  ck_assert_int_eq((int)Figure.block_type, i_block);
}
END_TEST

START_TEST(DropTimer) {
  ExtGameInfo_t* GameObject = ExtendedGameObjectInitialization();

  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_sec, 2);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_nsec, 0);

  GameObject->GameInfo->level = 2;
  changeDropTimer(GameObject);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_sec, 1);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_nsec, 950000000);

  GameObject->GameInfo->level = 3;
  changeDropTimer(GameObject);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_sec, 1);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_nsec, 900000000);

  GameObject->GameInfo->level = 4;
  changeDropTimer(GameObject);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_sec, 1);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_nsec, 800000000);

  GameObject->GameInfo->level = 5;
  changeDropTimer(GameObject);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_sec, 1);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_nsec, 650000000);

  GameObject->GameInfo->level = 6;
  changeDropTimer(GameObject);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_sec, 1);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_nsec, 400000000);

  GameObject->GameInfo->level = 7;
  changeDropTimer(GameObject);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_sec, 1);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_nsec, 200000000);

  GameObject->GameInfo->level = 8;
  changeDropTimer(GameObject);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_sec, 1);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_nsec, 0);

  GameObject->GameInfo->level = 9;
  changeDropTimer(GameObject);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_sec, 0);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_nsec, 800000000);

  GameObject->GameInfo->level = 10;
  changeDropTimer(GameObject);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_sec, 0);
  ck_assert_int_eq(GameObject->figure_drop_timer.delay.tv_nsec, 500000000);

  deleteGameField(GameObject->GameInfo);
}
END_TEST

START_TEST(readfileError) { ck_assert_int_eq(readHighScoreInfo(), -1); }
END_TEST

START_TEST(createfile) {
  createHighScoreInfoStorage();

  ck_assert_int_eq(readHighScoreInfo(), 0);
}
END_TEST

START_TEST(readfile) { ck_assert_int_eq(readHighScoreInfo(), 0); }
END_TEST

START_TEST(savefile) {
  saveHighScoreInfo(5);

  ck_assert_int_eq(readHighScoreInfo(), 5);
}
END_TEST

START_TEST(userinput) {
  ExtGameInfo_t* GameObject = ExtendedGameObjectInitialization();

  GameObject->state = SPAWN;
  userInput(Action, 0);
  ck_assert_int_ge(GameObject->curent_figure.color, 1);

  TetrisFigure_t FigureCopy;
  copy_figure_pos(&FigureCopy, &GameObject->curent_figure);
  userInput(Left, 0);
  ck_assert_int_eq(GameObject->curent_figure.blocks_position[0][0] -
                       FigureCopy.blocks_position[0][0],
                   -1);

  copy_figure_pos(&FigureCopy, &GameObject->curent_figure);
  userInput(Right, 0);
  ck_assert_int_eq(GameObject->curent_figure.blocks_position[0][0] -
                       FigureCopy.blocks_position[0][0],
                   1);

  copy_figure_pos(&FigureCopy, &GameObject->curent_figure);
  userInput(Down, 0);
  ck_assert_int_eq(GameObject->curent_figure.blocks_position[0][1] -
                       FigureCopy.blocks_position[0][1],
                   1);

  copy_figure_pos(&FigureCopy, &GameObject->curent_figure);
  GameObject->GameInfo->field[FigureCopy.blocks_position[0][1] + 1]
                             [FigureCopy.blocks_position[0][0]] = 3;
  userInput(Down, 0);
  ck_assert_int_ge(
      GameObject->GameInfo->field[FigureCopy.blocks_position[0][1]]
                                 [FigureCopy.blocks_position[0][0]],
      1);
  ck_assert_int_eq(GameObject->state, SPAWN);

  userInput((int)'c', 0);
  ck_assert_int_eq(GameObject->show_controls_keys, 1);
  userInput((int)'c', 0);
  ck_assert_int_eq(GameObject->show_controls_keys, 0);

  GameObject->state = GAMEOVER;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->state, START);

  GameObject->state = MOVING;
  userInput(Pause, 0);
  ck_assert_int_eq(GameObject->state, PAUSE);
  ck_assert_int_eq(GameObject->GameInfo->pause, TRUE);

  userInput(Start, 0);
  ck_assert_int_eq(GameObject->state, MOVING);
  ck_assert_int_eq(GameObject->GameInfo->pause, FALSE);

  userInput(Terminate, 0);
  ck_assert_int_eq(GameObject->state, EXIT_STATE);

  deleteGameField(GameObject->GameInfo);
}
END_TEST

START_TEST(rotate_test) {
  ExtGameInfo_t* GameObject = ExtendedGameObjectInitialization();

  choose_tetris_figure(i_block, &GameObject->next_figure);
  GameObject->state = SPAWN;
  userInput(Action, 0);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 1);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 0);

  choose_tetris_figure(j_block, &GameObject->next_figure);
  GameObject->state = SPAWN;
  userInput(Action, 0);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 1);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 2);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 3);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 0);

  choose_tetris_figure(l_block, &GameObject->next_figure);
  GameObject->state = SPAWN;
  userInput(Action, 0);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 1);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 2);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 3);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 0);

  choose_tetris_figure(o_block, &GameObject->next_figure);
  GameObject->state = SPAWN;
  userInput(Action, 0);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 0);

  choose_tetris_figure(s_block, &GameObject->next_figure);
  GameObject->state = SPAWN;
  userInput(Action, 0);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 1);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 0);

  choose_tetris_figure(z_block, &GameObject->next_figure);
  GameObject->state = SPAWN;
  userInput(Action, 0);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 1);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 0);

  choose_tetris_figure(t_block, &GameObject->next_figure);
  GameObject->state = SPAWN;
  userInput(Action, 0);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 1);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 2);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 3);
  GameObject->state = MOVING;
  userInput(Action, 0);
  ck_assert_int_eq(GameObject->curent_figure.rotate_case, 0);

  deleteGameField(GameObject->GameInfo);
}
END_TEST

START_TEST(timer_fast) {
  OG_timer_t timer;
  init_timer(&timer, 0, 60000000);

  char for_flag = check_timer_for_loops(&timer),
       single_flag = check_timer(timer);

  ck_assert_int_eq((int)for_flag, (int)'n');
  ck_assert_int_eq((int)single_flag, (int)'n');

  while (for_flag != 'y') {
    single_flag = check_timer(timer);
    if (single_flag == 'y') for_flag = check_timer_for_loops(&timer);
  }
  ck_assert_int_eq((int)for_flag, (int)'y');
  ck_assert_int_eq((int)single_flag, (int)'y');
}
END_TEST

START_TEST(timer_slow) {
  OG_timer_t timer;
  init_timer(&timer, 1, 30000000);

  char for_flag = check_timer_for_loops(&timer),
       single_flag = check_timer(timer);

  ck_assert_int_eq((int)for_flag, (int)'n');
  ck_assert_int_eq((int)single_flag, (int)'n');

  while (for_flag != 'y') {
    single_flag = check_timer(timer);
    if (single_flag == 'y') for_flag = check_timer_for_loops(&timer);
  }
  ck_assert_int_eq((int)for_flag, (int)'y');
  ck_assert_int_eq((int)single_flag, (int)'y');
}
END_TEST

// START_TEST() {

// }
// END_TEST

int main() {
  Suite* s1 = suite_create("Core");
  TCase* tc_core = tcase_create("Core");
  SRunner* sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc_core, get_GameInfo);
  tcase_add_test(tc_core, update_GameInfo);
  tcase_add_test(tc_core, get_ExtGameInfo);
  tcase_add_test(tc_core, update_ExtGameInfo);
  tcase_add_test(tc_core, get_signals);
  tcase_add_test(tc_core, GameInit);
  tcase_add_test(tc_core, ExtGameInit);
  tcase_add_test(tc_core, chooseFigure);
  tcase_add_test(tc_core, DropTimer);
  tcase_add_test(tc_core, readfileError);
  tcase_add_test(tc_core, createfile);
  tcase_add_test(tc_core, readfile);
  tcase_add_test(tc_core, savefile);
  tcase_add_test(tc_core, userinput);
  tcase_add_test(tc_core, rotate_test);
  tcase_add_test(tc_core, timer_fast);
  tcase_add_test(tc_core, timer_slow);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf ? 1 : 0;
}
