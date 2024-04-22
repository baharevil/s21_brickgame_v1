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

  if (!code) {
    pthread_t self_tid = pthread_self();
    pthread_detach(self_tid);
  }

  if (!code) {
    signals_unblock();
    pthread_mutex_lock(&runtime->stdout_mutex);
    initscr();
    set_signal_handler(gui_cli_resize);
    raw();
    box(stdscr, 0, 0);
    wprintw(stdscr, "Hi There !!!");
    wrefresh(stdscr);

    while (!atomic_load(&runtime->game_stop)) {
      // Такая передача по значению навязана нам заданием :(
      gui_cli_render(update_current_state());
      thread_wait(500);
    }
    cbreak();
    endwin();
    pthread_mutex_unlock(&runtime->stdout_mutex);
  }

  atomic_store(&runtime->gui_stop, 1);

  pthread_barrier_wait(&runtime->barrier);

  pthread_exit(0);
}