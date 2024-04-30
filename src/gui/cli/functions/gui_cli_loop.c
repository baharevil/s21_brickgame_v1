// TODO: Инициализация и запуск основного цикла
#include <errno.h>
#include <ncurses.h>
#include <pthread.h>
#include <signal.h>
#include <stddef.h>

#include "common/common.h"
#include "common/game_info_t.h"
#include "common/runtime_t.h"
#include "gui_cli.h"

void* gui_cli_loop(runtime_t* runtime) {
  extern game_info_t update_current_state();

  int code = 0;
  code = (runtime == NULL) * EFAULT;

  // if (!code) {
  //   // pthread_t self_tid = pthread_self();
  //   // pthread_detach(self_tid);
  // }

  if (!code) {
    signals_unblock();
    pthread_mutex_lock(&runtime->stdout_mutex);
    initscr();
    start_color();
    use_default_colors();
    set_signal_handler(gui_cli_resize);
    box(stdscr, 0, 0);
    wprintw(stdscr, "Tetris v.1");
    wrefresh(stdscr);

    while (!atomic_load(&runtime->game_stop)) {
      game_info_t game_info = {0};
      pthread_mutex_lock(&runtime->cond_mutex);
      pthread_cond_wait(&runtime->do_render, &runtime->cond_mutex);
      // Такая передача по значению навязана нам заданием :(
      game_info = update_current_state();
      if (game_info.field) gui_cli_render(game_info);
      pthread_mutex_unlock(&runtime->cond_mutex);
    }
    endwin();
    pthread_mutex_unlock(&runtime->stdout_mutex);
  }

  atomic_store(&runtime->gui_stop, 1);

  pthread_barrier_wait(&runtime->barrier);

  pthread_exit(0);
}