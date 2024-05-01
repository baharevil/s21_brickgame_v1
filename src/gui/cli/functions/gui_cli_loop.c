// TODO: Инициализация и запуск основного цикла
#include <errno.h>
// #include <ncurses.h>
#include <locale.h>
#include <pthread.h>
#include <signal.h>
#include <stddef.h>

#include "common/common.h"
#include "common/game_info_t.h"
#include "common/runtime_t.h"
#include "gui_cli.h"

/*
                  +------------------------------+ <--- game_windows_t
  game_win_t -----> +----------+ +-------------+ <----- stat_win_t
                  | | game_win | |   stat_win  | |
                  | |          | | +---------+ <------- support_win_t
                  | |          | | |   MAX   | | |
                  | |          | | |  99999  | | |
                  | |          | | +---------+ | |
                  | |          | | +---------+ <------- support_win_t
                  | |          | | |  SCORE  | | |
                  | |          | | |   100   | | |
                  | |          | | +---------+ | |
                  | |          | | +---------+ <------- support_win_t
                  | | *        | | |  LEVEL  | | |
                  | | **       | | |    1    | | |
                  | | *        | | +---------+ | |
                  | |          | | +---------+ <------- support_win_t
                  | |          | | |  NEXT   | | |
                  | |          | | |  ****   | | |
                  | |          | | +---------+ | |
                  | |          | | +---------+ <------- support_win_t
                  | |          | | |  INFO   | | |
                  | |  *    ** | | |  pause  | | |
                  | |**** * ** | | +---------+ | |
                  | +----------+ +-------------+ |
                  +------------------------------+
*/

void* gui_cli_loop(runtime_t* runtime) {
  extern game_info_t update_current_state();

  int code = 0;
  code = (runtime == NULL) * EFAULT;

  if (!code) {
    signals_block();
    signals_unblock();
    set_signal_handler(gui_cli_resize);
    pthread_mutex_lock(&runtime->stdout_mutex);

    setlocale(LC_CTYPE, ""); // Стоит перенести в init
    initscr();               // Стоит перенести в init
    // cbreak(); // Дерутся с
    // noecho(); // контроллером

    game_windows_t windows = {0};
    init_game_windows(&windows);
    update_panels();
    doupdate();

    while (!atomic_load(&runtime->game_stop)) {
      game_info_t game_info = {0};
      pthread_mutex_lock(&runtime->cond_mutex);
      pthread_cond_wait(&runtime->do_render, &runtime->cond_mutex);

      game_info = update_current_state();
      if (game_info.field) gui_cli_render(&windows, game_info);

      pthread_mutex_unlock(&runtime->cond_mutex);
    }

    del_game_windows(&windows);
    endwin();
    pthread_mutex_unlock(&runtime->stdout_mutex);
  }

  atomic_store(&runtime->gui_stop, 1);

  pthread_barrier_wait(&runtime->barrier);

  pthread_exit(0);
}