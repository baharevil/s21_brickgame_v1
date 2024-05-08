#ifndef GUI_CLI_H
#define GUI_CLI_H

#include <ncurses.h>
#include <panel.h>

#include "common/game_info_t.h"
#include "common/runtime_t.h"
#include "windows.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

enum game_filed_setting {
  field_higth = 20,
  field_windth = 10
};

enum brick_setting {
  brick_higth = 4,
  brick_windth = 4
};

void gui_cli_render(game_windows_t *windows, game_info_t *game_info);
int render_score(support_win_t *supp_win, int score);
int render_field(win_t *windows, int **field, int higth, int width,
                 char *label);

void gui_cli_resize();
int term_size(int *y, int *x);
void *gui_cli_loop(runtime_t *);

extern game_info_t update_current_state();

#endif