#include <stddef.h>
#include <malloc.h>
#include <locale.h>
#include <stdint.h>

#include "conroller_cli_tetris.h"

int main() {
  // init ncurses
  setlocale(LC_ALL, "");
  initscr();

  // main API logic
  game_loop();

  // end ncurses
  endwin();

  return 0;
}

void game_loop() {
  game_info_t game = {0};
  uint8_t breaking_flag = TRUE;

  while (breaking_flag) {
    // TODO State
    breaking_flag = FALSE;

    // TODO Uptade_cerent_state

    // TODO user_input
  }
}