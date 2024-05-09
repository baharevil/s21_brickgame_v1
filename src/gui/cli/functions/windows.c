#include "windows.h"

#include <errno.h>
#include <string.h>

game_windows_t *get_windows() {
  static game_windows_t windows = {0};
  return &windows;
}

int init_win(WINDOW *parent, win_t *child, win_data_t data, bool boxing) {
  if (!parent || !child) return EFAULT;

  child->win =
      derwin(parent, data.hight, data.width, data.start_y, data.start_x);
  child->data = data;
  if (boxing) box(child->win, 0, 0);

  wrefresh(child->win);
  wnoutrefresh(child->win);
  return 0;
}

int init_game_windows(game_windows_t *windows) {
  if (!windows) return EFAULT;

  // main_win
  init_win(stdscr, &(windows->main_win),
           (win_data_t){.start_x = 0,
                        .start_y = 0,
                        .hight = main_min_higth,
                        .min_hight = main_min_higth,
                        .width = main_min_width,
                        .min_width = main_min_width},
           TRUE);

  // game_win
  init_win(windows->main_win.win, &(windows->game_win),
           (win_data_t){.start_x = 1,
                        .start_y = 1,
                        .hight = game_min_higth,
                        .min_hight = game_min_higth,
                        .width = game_min_width,
                        .min_width = game_min_width},
           TRUE);

  // stat_win
  init_win(windows->main_win.win, &(windows->stat_win),
           (win_data_t){.start_x = 1 + game_min_width,
                        .start_y = 1,
                        .hight = game_min_higth,
                        .min_hight = game_min_higth,
                        .width = game_min_width,
                        .min_width = game_min_width},
           TRUE);

  // stats_windows
  char *labels[] = {"Hiscore", "Score", "Level", "Next"};
  for (int i = 0; i < count_support_win; i++) {
    init_win(windows->stat_win.win, &windows->stats_windows.windows[i].window,
             (win_data_t){.start_x = 1,
                          .start_y = 1 + i * support_min_higth,
                          .hight = support_min_higth,
                          .min_hight = support_min_higth,
                          .width = support_min_width,
                          .min_width = support_min_width},
             TRUE);
    windows->stats_windows.windows[i].show = TRUE;
    windows->stats_windows.windows[i].label = labels[i];
    mvwprintw(windows->stats_windows.windows[i].window.win, 1, 1, "%s",
              labels[i]);
    wrefresh(windows->stats_windows.windows[i].window.win);
  }
  return 0;
}

int del_game_windows(game_windows_t *windows) {
  if (windows == NULL) return EFAULT;

  for (int i = 0; i < count_support_win; i++) {
    delwin(windows->stats_windows.windows[i].window.win);
  }

  delwin(windows->stat_win.win);
  delwin(windows->game_win.win);
  delwin(windows->main_win.win);

  return 0;
}