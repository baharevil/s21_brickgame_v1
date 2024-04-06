//TODO: Инициализация и запуск основного цикла
#include <stddef.h>
#include <errno.h>
#include <pthread.h>

#include "../../../controller/runtime_t.h"
#include "tetris.h"

#include <stdio.h>

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
    while (!code && !atomic_load(&runtime->model_stop)) {
      if (atomic_load(&runtime->msg_to_model)) {
        userInput((UserAction_t)atomic_load(&runtime->msg_to_model), 0);
        atomic_store(&runtime->msg_to_model, 0);
      }
    }
  }

  pthread_exit(0);
}