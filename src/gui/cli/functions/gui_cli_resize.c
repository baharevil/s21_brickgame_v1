#include <ncurses.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#include "common/common.h"
#include "common/game_info_t.h"
#include "gui_cli.h"

void gui_cli_resize() {
  struct winsize ws = {0};
  ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
  clear();
  resizeterm(ws.ws_row, ws.ws_col);
  box(stdscr, 0, 0);
  
  refresh();

  int x = ws.ws_col / 2 - 20 / 2;
  int y = ws.ws_row / 2 - 1;

  if (ws.ws_row < 22 || ws.ws_col < 70)
    mvaddstr(y, x, "Screen too small :(");
  else
    mvaddstr(y, x, "                   ");
  refresh();

  set_signal_handler(gui_cli_resize);
}