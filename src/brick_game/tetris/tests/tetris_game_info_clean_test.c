#include <errno.h>
#include <check.h>
#include <stdbool.h>

#include "tetris.h"

START_TEST(suite_game_info_clean_test1) {
  int result = 0;
  result = game_info_clean(NULL);
  ck_assert_int_eq(result, EINVAL);
} END_TEST

START_TEST(suite_game_info_clean_test2) {
  int result = 0;
  game_info_t *game_info = NULL;
  game_info_init(&game_info);
  result = game_info_clean(game_info);
  game_info_destroy(game_info);
  ck_assert_int_eq(result, 0);
} END_TEST

Suite * suite_game_info_clean() {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("\x1b[1;33m-=suite_game_info_clean=-\x1b[0m");

  tc = tcase_create("suite_game_info_clean");
  tcase_add_test(tc, suite_game_info_clean_test1);
  tcase_add_test(tc, suite_game_info_clean_test2);

  suite_add_tcase(s, tc);

  return s;
}