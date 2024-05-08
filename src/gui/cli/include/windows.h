#ifndef WINDOWS_H
#define WINDOWS_H

#include <panel.h>
#include <ncurses.h>

enum window_setting {
  main_min_higth = 24,
  main_min_width = 46,
  game_min_higth = 22,
  game_min_width = 22,
  support_min_higth = 5,
  support_min_width = 20,
  count_support_win = 4
};

typedef struct __win_data {
  int start_x, start_y;
  int hight, width;
  int min_hight, min_width;
} win_data_t;

typedef struct __windows {
  WINDOW *win;
  win_data_t data;
} win_t;

typedef struct __support_win {
  win_t window;

  char *label;
  bool show;
} support_win_t;

typedef union __stats_win {
  support_win_t windows[count_support_win];
  struct {
    support_win_t max_win;
    support_win_t score_win;
    support_win_t level_win;
    support_win_t next_win;
  };
} stats_wins_t;

typedef struct __game_windows {
  win_t main_win;
  win_t game_win;
  win_t stat_win;
  stats_wins_t stats_windows;
} game_windows_t;

game_windows_t *get_windows();
int init_win(WINDOW *parent, win_t *child, win_data_t data, bool boxing);
int init_game_windows(game_windows_t *windows);
int del_game_windows(game_windows_t *windows);

#endif