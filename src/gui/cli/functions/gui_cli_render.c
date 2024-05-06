#include "common/game_info_t.h"
#include "gui_cli.h"

void gui_cli_render(game_windows_t *windows, game_info_t game_info) {
  if (!windows) return;

  int term_x = 0, term_y = 0;
  term_size(&term_y, &term_x);
  windows->game.field = game_info.field;
  if (term_y > 24 || term_x > 46) render_field(&(windows->game));
  // TODO render_next, render_score, render_max, render_level
  update_panels();
  doupdate();
  curs_set(0);

  // refresh();
}

void render_field(game_win_t *game) {
  if (!game) return;

  wclear(game->win.win);
  box(game->win.win, 0, 0);
  for (int row = 0; row < field_height; row++) {
    for (int col = 0; col < field_width; col++) {
      if (game->field[row][col])
        mvwaddch(game->win.win, row + 1, col * 2 + 1, ACS_DEGREE);
    }
  }
  curs_set(0);
  wrefresh(game->win.win);
}
