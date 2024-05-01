#include <errno.h>
#include <malloc.h>
#include <string.h>

#include "gui_cli.h"

// TODO: set_panel_userptr fpr pause_panel
int init_game_windows(game_windows_t *windows) {
  if (windows == NULL) return EFAULT;

  win_panel_data_t data = {0};

  // game_windows_t
  data.hight = WINLIN + 2;
  data.width = data.hight + 2;
  init_win(stdscr, &(windows->win), &data);

  // game_win_t
  data.hight = WINLIN;
  data.width = WINCOL;
  data.start_x = data.start_y = 1;
  init_win(windows->win.win, &(windows->game.win), &data);

  // stat_win_t
  data.start_x += data.width;
  init_win(windows->win.win, &(windows->stat.win), &data);

  windows->stat.count_stats = 4;
  char *labels[] = {"MAX", "SCORE", "LEVEL", "NEXT"};
  windows->stat.stats =
      calloc(windows->stat.count_stats, sizeof(support_win_t));

  // stat_win_t -> support_win_t
  for (int i = 0; i < windows->stat.count_stats; i++) {
    init_support_win(windows->stat.win.win, &(windows->stat.stats[i]),
                     windows->stat.count_stats, i, labels[i]);
  }

  return EXIT_SUCCESS;
}

int init_win(WINDOW *orig, win_panel_t *win, win_panel_data_t *data) {
  if (!win || !data || !orig) return EFAULT;

  win->win =
      derwin(orig, data->hight, data->width, data->start_y, data->start_x);
  win->panel = new_panel(win->win);
  win->data = *data;
  box(win->win, 0, 0);

  return EXIT_SUCCESS;
}

int init_support_win(WINDOW *parent, support_win_t *current, int count_win,
                     int ordinal, char *label) {
  if (!parent || !current || !label) return EFAULT;

  win_panel_data_t data = {0};
  data.hight = (getmaxy(parent) - 2) / count_win;
  data.width = getmaxx(parent) - 2;
  data.start_x = 1;
  data.start_y = 1 + ordinal * data.hight;
  init_win(parent, &(current->win), &data);

  int str_len = strlen(label);
  mvwprintw(current->win.win, 1, (data.width - str_len + 1) / 2, "%s", label);
  wrefresh(current->win.win);

  return EXIT_SUCCESS;
}
