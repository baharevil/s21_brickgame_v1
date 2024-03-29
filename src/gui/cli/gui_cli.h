#ifndef GUI_CLI_H
#define GUI_CLI_H

#include "../../controller/controller.h"

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

int gui_init(runtime_t *);
int gui(pthread_cond_t *, pthread_mutex_t *);

// Точка входа потока
void* (*model_loop)(void*) = (void* (*)(void*))gui_init; 

int render(int **);

void userInput(UserAction_t action, int hold);

#endif