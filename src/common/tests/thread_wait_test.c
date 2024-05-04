#include <errno.h>
#include <check.h>

#include "common.h"

START_TEST(thread_wait_test1) {
  int retval = 0;
  retval = thread_wait(0);
  ck_assert_int_eq(retval, EINVAL);
} END_TEST

Suite * suite_thread_wait() {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("suite_thread_wait");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, thread_wait_test1);

  return s;
}