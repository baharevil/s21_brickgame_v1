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
  TCase *tc_core = NULL;

  s = suite_create("suite_tetris_loop");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, suite_tetris_loop1);

  return s;
}