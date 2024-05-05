#include <errno.h>
#include <check.h>
#include <stdbool.h>
#include <pthread.h>

#include "common/common.h"
#include "tetris.h"

START_TEST(suite_tetris_loop_test1) {
  void *result = NULL;
  result = tetris_loop(NULL);
  ck_assert_ptr_eq(result, (void *)EFAULT);
} END_TEST

START_TEST(suite_tetris_loop_test2) {
  void *result = NULL;
  runtime_t runtime = {0};
  pthread_barrier_init(&runtime.barrier, NULL, 1);
  pthread_create(&runtime.model, NULL, (void* (*)(void *))tetris_loop, (void*)&runtime);
  thread_wait(100);
  runtime.game_stop = 1;
  pthread_join(runtime.model, (void*)result);
  pthread_barrier_destroy(&runtime.barrier);
  ck_assert_ptr_eq(result, (void *)0);
} END_TEST

Suite * suite_tetris_loop() {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("\x1b[1;33m-=suite_tetris_loop=-\x1b[0m");

  tc = tcase_create("suite_tetris_loop");
  tcase_add_test(tc, suite_tetris_loop_test1);
  tcase_add_test(tc, suite_tetris_loop_test2);

  suite_add_tcase(s, tc);

  return s;
}