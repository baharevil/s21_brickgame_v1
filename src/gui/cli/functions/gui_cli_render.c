#include <ncurses.h>
#include <string.h>

#include "common/game_info_t.h"
#include "gui_cli.h"

void gui_cli_render(game_info_t game_info) {
  // wborder(stdscr, 1, 2, 3, 4, 1, 2, 3, 4);
  for (int row = 0; row < field_height; row++) {
    for (int col = 0; col < field_width; col++) {
      if (game_info.field[row][col]) {
        mvwaddch(stdscr, 2 + row, 5 + col * 2, 48);
      } else {
        mvwaddch(stdscr, 2 + row, 5 + col * 2, 32);
      }
    }
  }
  refresh();
}