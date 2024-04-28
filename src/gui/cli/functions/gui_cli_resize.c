#include <ncurses.h>
#include <signal.h>
#include <string.h>

#include "common/common.h"
#include "common/game_info_t.h"
#include "gui_cli.h"

void gui_cli_resize() {
  endwin();
  clear();
  initscr();
  refresh();

  char tmp[128];
  sprintf(tmp, "%dx%d", COLS, LINES);

  int x = COLS / 2 - strlen(tmp) / 2;
  int y = LINES / 2 - 1;

  box(stdscr, 0, 0);
  if (LINES < 22 || COLS < 70)
    mvaddstr(y, x, "Screen too small :(");
  else
    mvaddstr(y, x, tmp);
  refresh();

  // TODO:
  // Попробовать получить новые значения размеров окна(!) main_window
  // без переинициализации всего ncurses (initscr());
  // В таком случае можно будет удалить окно main_window и создать его заново.
  // signal(SIGWINCH, gui_cli_resize);
  set_signal_handler(gui_cli_resize);
}