#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "controller.h"

int controller_loop(runtime_t *runtime) {
  int code = 0;

  code = (runtime == NULL) * EFAULT;
  
  if (!code) {
    runtime_t *data = (runtime_t *)runtime;
    while (!data->game_stop) {

        // устанавливаем блокировку
        pthread_mutex_lock(&data->mutex);
        // Операции ввода-вывода, изменение переменных, памяти.
        printf("Controller check.\n");  
        // снимаем блокировку
        pthread_mutex_unlock(&data->mutex);

        sleep(1);
    }
  }
  return code;
}
