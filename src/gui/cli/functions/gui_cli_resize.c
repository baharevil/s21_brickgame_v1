#include <ncurses.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#include "common/common.h"
#include "common/game_info_t.h"
#include "gui_cli.h"

void gui_cli_resize() {
  int x = 0, y = 0;
  term_size(&y, &x);
  
  resizeterm(y, x);
  if (y < 24 || x < 46)
    clear();
  // box(stdscr, 0, 0);
  curs_set(0);
  refresh();

  set_signal_handler(gui_cli_resize);
}