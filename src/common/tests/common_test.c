#include <stdio.h>

#include "common_test.h"

void run_test_case(Suite *testcase) {
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
    suite_thread_wait(),
    // suite_time_msec(),
    // suite_signals_block(),
    // suite_signals_unblock(),
    // suite_set_signal_handler(),
    NULL
  };

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