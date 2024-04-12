#ifndef GUI_CLI_H
#define GUI_CLI_H

#include "common/runtime_t.h"
#include "common/game_info_t.h"

/*TODO:
GUI_CLI function here:
- Input
- Render
*/

void * gui_cli_loop(runtime_t *);

int render(int **);

#endif