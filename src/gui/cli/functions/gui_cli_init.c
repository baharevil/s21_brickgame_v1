//TODO: Инициализация и запуск основного цикла
#include <stddef.h>
#include <errno.h>
#include <pthread.h>

#include "../../../controller/runtime_t.h"
#include "gui_cli.h"

void* gui_cli_init(runtime_t *runtime) {
  int code = 0;

  code = (runtime == NULL) * EFAULT;
  
  if (!code) {
    runtime_t *data = (runtime_t *)runtime;
    pthread_t self_tid = pthread_self();
    
    pthread_mutex_lock(&data->mutex);
    data->gui = self_tid;
    pthread_mutex_unlock(&data->mutex);    
    
    /* No other thread is going to join() this one - прикольно,
    * самоотсоединение:*/
    pthread_detach(self_tid);
  }

  if (!code) {
    // UserAction_t action = {0};
    code = gui_cli_loop(&runtime->do_input, &runtime->mutex);
  }

  pthread_exit(0);
}