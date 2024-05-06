#include <check.h>
#include <stdio.h>

#include "tetris.h"

START_TEST(suite_figure_load_test1) {
  figure_t *figure = NULL;
  figure = figure_load(NULL);
  ck_assert_ptr_null(figure);
}
END_TEST

START_TEST(suite_figure_load_test2) {
  figure_t *figure = NULL;
  FILE *file = NULL;
  file = fopen("./figures/hero.tet", "rb");
  if (file) {
    figure = figure_load(file);
    ck_assert_ptr_nonnull(figure);
    figure_destroy(figure);
    fclose(file);
  }
}
END_TEST

Suite *suite_figure_load() {
  Suite *s = NULL;
  TCase *tc = NULL;

  s = suite_create("\x1b[1;33m-=suite_figure_load=-\x1b[0m");
  tc = tcase_create("suite_figure_load");

  if (s && tc) {
    tcase_add_test(tc, suite_figure_load_test1);
    tcase_add_test(tc, suite_figure_load_test2);
    suite_add_tcase(s, tc);
  }

  return s;
}