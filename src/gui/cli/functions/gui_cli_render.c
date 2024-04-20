#include <ncurses.h>
#include <string.h>

#include "common/game_info_t.h"
#include "gui_cli.h"

void gui_cli_render(game_info_t game_info) {
  // TODO: render()
  char tmp[128];
  for (int row = 0; row < field_height; row++) {
    for (int col = 0; col < field_width; col++) {
      if (game_info.field[row][col])
        tmp[col] = (unsigned char) 254;
      tmp[col + 1] = 0;
    }
    // mvprintw(row, 1, tmp);
    mvaddstr(row, COLS / 2 - field_width / 2, tmp);
  }
  refresh();
}