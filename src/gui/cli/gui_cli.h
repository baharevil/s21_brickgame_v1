#ifndef GUI_CLI_H
#define GUI_CLI_H

#include "common/runtime_t.h"
#include "common/game_info_t.h"

enum windows_names { game_logo, main_window, next, game_stats };

void * gui_cli_loop(runtime_t *);
void gui_cli_resize();
void gui_cli_render(game_info_t);

extern game_info_t update_current_state();

#endif