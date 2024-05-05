#include <errno.h>
#include <check.h>
#include <stdbool.h>

#include "tetris.h"

START_TEST(suite_game_destroy_test1) {
  int result = 0;
  result = game_init(NULL);
  ck_assert_int_eq(result, EINVAL);
} END_TEST

START_TEST(suite_game_destroy_test2) {
  int result = 0;
  game_t *game = NULL;
  game_init(&game);
  result = game_destroy(game);
  ck_assert_int_eq(result, 0);
} END_TEST

Suite * suite_game_destroy() {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("\x1b[1;33m-=suite_game_destroy=-\x1b[0m");

  tc = tcase_create("suite_game_destroy");
  tcase_add_test(tc, suite_game_destroy_test1);
  tcase_add_test(tc, suite_game_destroy_test2);

  suite_add_tcase(s, tc);

  return s;
}