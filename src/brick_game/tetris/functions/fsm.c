#include <stddef.h>
#include <errno.h>

#include "tetris.h"

action fsm(fsm_state state, UserAction_t user_action) {
    action result = NULL;

    action fsm_matrix[8][8] = {\
  // Start  Pause Term       Left  Right Up    Down  none
    {start_fn, NULL, terminate_fn, NULL, NULL, NULL, NULL, NULL}, // Start
    {NULL, pause_fn, terminate_fn, NULL, NULL, NULL, NULL, NULL}, // Pause
    {NULL,  NULL, terminate_fn, NULL, NULL, NULL, NULL, NULL}, // Spawn
    {NULL, pause_fn, terminate_fn, left_fn, right_fn, up_fn,  down_fn, NULL}, // Move
    {NULL,  NULL, terminate_fn, NULL, NULL, NULL, NULL, NULL}, // Shift
    {NULL,  NULL, terminate_fn, NULL, NULL, NULL, NULL, NULL}, // Connect
    {start_fn, NULL, terminate_fn, NULL, NULL, NULL, NULL, NULL}, // Game Over
    {NULL,  NULL, NULL,      NULL, NULL, NULL, NULL, NULL}};// Terminate
    
    result = fsm_matrix[state][(int)user_action];
    return result;
}