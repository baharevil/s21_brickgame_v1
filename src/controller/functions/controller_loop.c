#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "controller.h"

void* controller_loop(runtime_t *runtime) {
  int code = 0;

  code = (runtime == NULL) * EFAULT;
  
  if (!code) {
    pthread_t self_tid = pthread_self();
    runtime->controller = self_tid;
    
    /* No other thread is going to join() this one - прикольно,
    * самоотсоединение:*/
    pthread_detach(self_tid);
  }

  if (!code) {
    int count = 5;
    // runtime_t *data = (runtime_t *)runtime;
    while (!runtime->game_stop) {
        // устанавливаем блокировку
        pthread_mutex_lock(&runtime->stdout_mutex);
        // Операции ввода-вывода, изменение переменных, памяти.
        printf("Controller check %d\n", count--);
        // снимаем блокировку
        pthread_mutex_unlock(&runtime->stdout_mutex);

        runtime->game_stop = (count < 1);
        sleep(1);
    }
  }
  pthread_exit(0);
}
