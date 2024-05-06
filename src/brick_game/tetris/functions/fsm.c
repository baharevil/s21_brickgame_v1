#include <errno.h>
#include <stddef.h>

#include "tetris.h"

action fsm(fsm_state state, UserAction_t user_action) {
  action result = NULL;

  action fsm_matrix[8][9] = {
      // None  Start Pause Term  Left  Right Up    Down  Action
      {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
       NULL},  // none (terminate)
      {NULL, start_fn, NULL, terminate_fn, NULL, NULL, NULL, NULL,
       NULL},  // start
      {NULL, NULL, pause_fn, terminate_fn, NULL, NULL, NULL, NULL,
       NULL},                                                          // pause
      {NULL, NULL, NULL, terminate_fn, NULL, NULL, NULL, NULL, NULL},  // spawn
      {NULL, NULL, pause_fn, terminate_fn, left_fn, right_fn, up_fn, down_fn,
       action_fn},                                             // move
      {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},  // shift
      {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},  // connect
      {NULL, start_fn, NULL, terminate_fn, NULL, NULL, NULL, NULL,
       NULL}};  // game over

  result = fsm_matrix[state][(int)user_action];
  return result;
}