//TODO: Инициализация и запуск основного цикла
#include <stddef.h>
#include <errno.h>
#include <pthread.h>

#include "../../../controller/controller.h"

void *tetris_init(void *runtime) {
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

  pthread_exit(0);
}