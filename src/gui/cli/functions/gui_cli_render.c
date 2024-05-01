

#include "common/game_info_t.h"
#include "gui_cli.h"

void gui_cli_render(game_windows_t *windows, game_info_t game_info) {
  if (!windows) return;

  windows->game.field = game_info.field;
  render_field(&(windows->game));
  // TODO render_next, render_score, render_max, render_level
  update_panels();
  doupdate();

  refresh();
}

void render_field(game_win_t *game) {
  if (!game) return;

  wclear(game->win.win);
  box(game->win.win, 0, 0);
  for (int row = 0; row < field_height; row++) {
    for (int col = 0; col < field_width; col++) {
      if (game->field[row][col]) mvwaddch(game->win.win, row + 1, col + 1, ACS_DEGREE);
    }
  }
  wrefresh(game->win.win);

}
