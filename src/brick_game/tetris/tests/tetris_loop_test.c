#include <errno.h>
#include <check.h>

#include "tetris.h"

START_TEST(suite_tetris_loop1) {
  void *result = NULL;
  result = tetris_loop(NULL);
  ck_assert_ptr_eq(result, (void *)EFAULT);
} END_TEST

Suite * suite_tetris_loop() {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("\x1b[1;33m-=suite_tetris_loop=-\x1b[0m");

  tc = tcase_create("suite_tetris_loop");
  tcase_add_test(tc, suite_tetris_loop1);

  suite_add_tcase(s, tc);

  return s;
}