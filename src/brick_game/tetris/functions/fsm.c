#include <stddef.h>
#include <errno.h>

#include "tetris.h"

action fsm(fsm_state state, UserAction_t user_action) {
    action result = NULL;

    action fsm_matrix[9][8] = {\
  // None  Start  Pause    Term         Left  Right Up    Down  none
    {NULL, NULL,  NULL,    NULL,         NULL, NULL, NULL, NULL}, // none
    {NULL, start_fn, NULL, terminate_fn, NULL, NULL, NULL, NULL}, // start
    {NULL, NULL, pause_fn, terminate_fn, NULL, NULL, NULL, NULL}, // pause
    {NULL, NULL,  NULL,    terminate_fn, NULL, NULL, NULL, NULL}, // spawn
    {NULL, NULL, pause_fn, terminate_fn, left_fn, right_fn, up_fn,  down_fn}, // move
    {NULL, NULL,  NULL,    NULL,         NULL, NULL, NULL, NULL}, // shift
    {NULL, NULL,  NULL,    terminate_fn, NULL, NULL, NULL, NULL}, // connect
    {NULL, start_fn, NULL, terminate_fn, NULL, NULL, NULL, NULL}, // game over
    {NULL, NULL,  NULL,    NULL,         NULL, NULL, NULL, NULL}};// terminate
    
    result = fsm_matrix[state][(int)user_action];
    return result;
}