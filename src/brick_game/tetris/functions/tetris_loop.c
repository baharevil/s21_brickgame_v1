//TODO: Инициализация и запуск основного цикла
#include <stddef.h>
#include <errno.h>
#include <pthread.h>

#include "../../../controller/runtime_t.h"
#include "tetris.h"

void* tetris_loop(runtime_t *runtime) {
  int code = 0;

  code = (runtime == NULL) * EFAULT;
  
  if (!code) {
    pthread_t self_tid = pthread_self();
    runtime->model = self_tid;
    
    /* No other thread is going to join() this one - прикольно,
    * самоотсоединение:*/
    pthread_detach(self_tid);
  }

  if (!code) {
    // game_t game = {0};
    while (runtime->model_stop) {
        // endless
    }
  }

  pthread_exit(0);
}