//TODO: Инициализация и запуск основного цикла
#include <stddef.h>
#include <errno.h>
#include <pthread.h>

#include "../../../controller/runtime_t.h"
#include "tetris.h"

void* tetris_init(runtime_t *runtime) {
  int code = 0;

  code = (runtime == NULL) * EFAULT;
  
  if (!code) {
    runtime_t *data = (runtime_t *)runtime;
    pthread_t self_tid = pthread_self();
    
    pthread_mutex_lock(&data->mutex);
    data->model = self_tid;
    pthread_mutex_unlock(&data->mutex);    
    
    /* No other thread is going to join() this one - прикольно,
    * самоотсоединение:*/
    pthread_detach(self_tid);
  }

  if (!code) {
    game_t game = {0};
    tetris_loop(&game);
  }

  pthread_exit(0);
}