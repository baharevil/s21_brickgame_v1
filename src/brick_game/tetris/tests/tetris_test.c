#include "tetris_test.h"

#include <stdio.h>

void run_test_case(Suite *testcase) {
  // TestResult *result = {0};
  // result = srunner_results(srunner);
  SRunner *srunner = {0};
  srunner = srunner_create(testcase);
  if (srunner) {
    srunner_set_fork_status(srunner, CK_NOFORK);
    srunner_run_all(srunner, CK_NORMAL);
    srunner_free(srunner);
  }
}

void run_tests() {
  int testcase_counter = 0;
  Suite *list_cases[] = {
      suite_tetris_loop(), suite_game_locate(), suite_game_init(),
      suite_game_destroy(), suite_game_info_init(), suite_game_info_clean(),
      suite_game_info_destroy(), suite_game_info_next_init(),
      suite_game_info_next_destroy(), suite_figure_db_load(),
      suite_figure_db_insert(), suite_figure_db_destroy(),
      suite_figure_create(), suite_figure_destroy(), suite_figure_load(),
      suite_figure_copy(), suite_figure_copy_body(), suite_figure_set(),
      suite_figure_unset(), suite_figure_rotate(), suite_figure_check(),
      suite_kaboom(), suite_fsm(),
      // suite_start_fn(),
      // suite_pause_fn(),
      // suite_spawn_fn(),
      // suite_move_fn(),
      // suite_shift_fn(),
      // suite_connect_fn(),
      // suite_game_over_fn(),
      // suite_terminate_fn(),
      // suite_left_fn(),
      // suite_right_fn(),
      // suite_up_fn(),
      // suite_down_fn(),
      // suite_action_fn(),
      // suite_userInput(),
      // suite_update_current_state(),
      NULL};

  while (list_cases[testcase_counter] != NULL) {
    run_test_case(list_cases[testcase_counter]);
    putc('\n', stdout);
    testcase_counter++;
  }
}

int main() {
  run_tests();
  return 0;
}