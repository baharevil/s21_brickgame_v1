#ifndef GUI_CLI_H
#define GUI_CLI_H

#include "../../controller/runtime_t.h"

#include "../../brick_game/tetris/game_info_t.h"

/*TODO:
GUI_CLI function here:
- Input
- Render
*/

int height = 20, width = 10;

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

void * gui_cli_init(runtime_t *);
int gui_cli_loop(pthread_cond_t *, pthread_mutex_t *);

int render(int **);

void userInput(UserAction_t action, int hold);

#endif