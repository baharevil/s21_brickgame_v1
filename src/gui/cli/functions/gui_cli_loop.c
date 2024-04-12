//TODO: Инициализация и запуск основного цикла
#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <ncurses.h>

#include "common/runtime_t.h"
#include "gui_cli.h"

void* gui_cli_loop(runtime_t *runtime) {
  int code = 0;

  code = (runtime == NULL) * EFAULT;
  
  if (!code) {
    pthread_t self_tid = pthread_self();
    // runtime->gui = self_tid;
    
    /* No other thread is going to join() this one - прикольно,
    * самоотсоединение:*/
    pthread_detach(self_tid);
  }

  if (!code) {
    // UserAction_t action = {0};
    while (!atomic_load(&runtime->game_stop)) {
        // endless
    }
  }
  
  atomic_store(&runtime->gui_stop, 1);

  pthread_barrier_wait(&runtime->barrier);

  pthread_exit(0);
}