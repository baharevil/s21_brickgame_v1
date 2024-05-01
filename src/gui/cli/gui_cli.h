#ifndef GUI_CLI_H
#define GUI_CLI_H

#include <ncurses.h>
#include <panel.h>

#include "common/game_info_t.h"
#include "common/runtime_t.h"

#define WINLIN 22
#define WINCOL 12

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

enum windows_names { game_logo, main_window, next, game_stats };

typedef struct win_panel_data_t {
  int start_x, start_y;
  int hight, width;
} win_panel_data_t;

typedef struct win_panel_t {
  WINDOW *win;
  PANEL *panel;
  win_panel_data_t data;
} win_panel_t;

typedef struct support_win_t {
  win_panel_t win;

  char *label;
  void *data;
} support_win_t;

typedef struct game_win_t {
  win_panel_t win;

  int **field;
} game_win_t;

typedef struct stat_win_t {
  win_panel_t win;
  support_win_t *stats;

  int count_stats;
} stat_win_t;

typedef struct game_windows_t {
  win_panel_t win;

  game_win_t game;
  stat_win_t stat;
  support_win_t pause;
} game_windows_t;

int init_game_windows(game_windows_t *windows);
int del_game_windows(game_windows_t *windows);

int init_support_win(WINDOW *parent, support_win_t *current, int count_win,
                     int ordinal, char *label);
int init_win(WINDOW *orig, win_panel_t *win, win_panel_data_t *data);
int del_win(win_panel_t *win);

void render_field(game_win_t *game);

void *gui_cli_loop(runtime_t *);
void gui_cli_resize();
void gui_cli_render(game_windows_t *, game_info_t);

extern game_info_t update_current_state();

#endif