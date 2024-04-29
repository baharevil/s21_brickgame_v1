#include <ncurses.h>
#include <string.h>

#include "common/game_info_t.h"
#include "gui_cli.h"

void gui_cli_render(game_info_t game_info) {
  // wborder(stdscr, 1, 2, 3, 4, 1, 2, 3, 4);
  mvwprintw(stdscr, 1, 5, "-------------------");
  for (int row = 0; row < field_height; row++) {
    for (int col = 0; col < field_width; col++) {
      mvwprintw(stdscr, 1 + row, 4, "|");
      if (game_info.field[row][col]) {
        mvwprintw(stdscr, 2 + row, 5 + col * 2, "%c", 'o');
      } else {
        mvwprintw(stdscr, 2 + row, 5 + col * 2, "%c", 32);
      }
      mvwprintw(stdscr, 1 + row, 24, "|");
    }
  }
  mvwprintw(stdscr, 21, 4, "|");
  mvwprintw(stdscr, 21, 24, "|");
  mvwprintw(stdscr, 22, 5, "-------------------");
  refresh();
}