#include <errno.h>

#include "common/game_info_t.h"
#include "gui_cli.h"

void gui_cli_render(game_windows_t *windows, game_info_t game_info) {
  if (!windows) return;

  int term_x = 0, term_y = 0;
  term_size(&term_y, &term_x);
  render_field(&windows->game_win, game_info.field);
  render_next(&windows->stats_windows.next_win, game_info.next);

  doupdate();
}

int render_field(win_t *windows, int **field) {
  if (!windows || !field) return EFAULT;

  wclear(windows->win);
  box(windows->win, 0, 0);

  for (int row = 0; row < field_height; row++) {
    for (int col = 0; col < field_width; col++) {
      if (field[row][col]) 
        mvwaddstr(windows->win, 1 + row, 1 + 2 * col, "[]");
    }
  }

  wnoutrefresh(windows->win);
  return 0;
}

int render_next(support_win_t *windows, int **next) {
  if (!windows || !next) return EFAULT;

  wclear(windows->window.win);
  box(windows->window.win, 0, 0);

  for (int i = 0; i < brick_higth; i++) {
    for (int j = 0; j < brick_windth; j++)
      if (next[i][j]) mvwaddstr(windows->window.win, 1 + j, 1 + 2 * i, "[]");
  }

  mvwprintw(windows->window.win, 1, 1, "%s", windows->label);

  wnoutrefresh(windows->window.win);
  return 0;
}
