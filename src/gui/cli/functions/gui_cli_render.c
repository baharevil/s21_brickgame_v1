#include <errno.h>
#include <string.h>

#include "common/game_info_t.h"
#include "gui_cli.h"

void gui_cli_render(game_windows_t *windows, game_info_t *game_info) {
  if (!windows) return;

  static int stored_x = 0, stored_y = 0, stored_hs = 0, stored_s = 0, stored_l = 0;
  int term_x = 0, term_y = 0, resized = 0;
  term_size(&term_y, &term_x);
  
  resized = (stored_x != term_x || stored_y != term_y);

  render_field(&windows->game_win, game_info->field, field_height, field_width, NULL);
  // !Bug with next btick  
  render_field(&windows->stats_windows.next_win.window, game_info->next,
               brick_higth, brick_windth,
               windows->stats_windows.next_win.label);

  if (resized || stored_hs != game_info->high_score) {
    render_score(&windows->stats_windows.max_win, game_info->high_score);
    stored_hs = game_info->high_score;
  }
  if (resized || stored_s != game_info->score) {
    render_score(&windows->stats_windows.score_win, game_info->score);
    stored_s = game_info->score;
  }
  if (resized || stored_l != game_info->level) {
    render_score(&windows->stats_windows.level_win, game_info->level);
    stored_l = game_info->level;
  }
  // Тут не попал
  if (resized) {
    box(windows->main_win.win, 0, 0);
    box(windows->game_win.win, 0, 0);
    box(windows->stat_win.win, 0, 0);
  }

  doupdate();
}

int render_field(win_t *windows, int **field, int higth, int width,
                 char *label) {
  if (!windows || !field) return EFAULT;

  init_pair(1, 0, COLOR_RED);
  init_pair(2, 0, COLOR_GREEN);
  init_pair(3, 0, COLOR_YELLOW);
  init_pair(4, 0, COLOR_BLUE);
  init_pair(5, 0, COLOR_MAGENTA);
  init_pair(6, 0, COLOR_CYAN);
  init_pair(7, 0, COLOR_WHITE);
  
  // clear
  // wclear(windows->win);
  box(windows->win, 0, 0);

  // render
  for (int i = 0; i < higth; i++) {
    for (int j = 0; j < width; j++)
      if (field[i][j]) {
        wattrset(windows->win, COLOR_PAIR(field[i][j]));
        mvwaddstr(windows->win, 1 + i, 1 + 2 * j, "  ");
        wattrset(windows->win, 0);
      } 
      else mvwaddstr(windows->win, 1 + i, 1 + 2 * j, "  ");
  }
  if (label) mvwaddstr(windows->win, 1, 1, label);

  // flag_to_update
  wnoutrefresh(windows->win);
  return 0;
}

int render_score(support_win_t *supp_win, int score) {
  if (!supp_win) return EFAULT;
  
  // clear 
  // wclear(supp_win->window.win);
  box(supp_win->window.win, 0, 0);

  // render
  char buffer[128] = {0};
  sprintf(buffer, "%d", score);
  mvwaddstr(supp_win->window.win, supp_win->window.data.hight - 2,
            supp_win->window.data.width - strlen(buffer) - 1, buffer);

  attron(A_BOLD);
  mvwaddstr(supp_win->window.win, 1, 1, supp_win->label);
  attroff(A_BOLD);

  // flag_to_update
  wnoutrefresh(supp_win->window.win);
  return 0;
}
