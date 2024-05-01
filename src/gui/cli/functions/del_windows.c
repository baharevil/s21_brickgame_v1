#include <errno.h>
#include <malloc.h>

#include "gui_cli.h"

int del_game_windows(game_windows_t *windows) {
  if (windows == NULL) return EFAULT;

  del_win(&(windows->win));
  del_win(&(windows->game.win));
  del_win(&(windows->stat.win));

  for (int i = 0; i < windows->stat.count_stats; i++) {
    del_win(&(windows->stat.stats[i].win));
  }

  free(windows->stat.stats);

  return EXIT_SUCCESS;
}

int del_win(win_panel_t *win) {
  if (win == NULL) return EFAULT;

  del_panel(win->panel);
  delwin(win->win);

  return EXIT_SUCCESS;
}