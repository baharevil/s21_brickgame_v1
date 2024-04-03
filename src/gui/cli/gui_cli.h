#ifndef GUI_CLI_H
#define GUI_CLI_H

#include "../../controller/runtime_t.h"
#include "../../brick_game/tetris/game_info_t.h"

/*TODO:
GUI_CLI function here:
- Input
- Render
*/

typedef enum { height = 20, width = 10 } field_size;

void * gui_cli_loop(runtime_t *);

int render(int **);

#endif