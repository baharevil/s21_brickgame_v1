#include <stddef.h>
#include <errno.h>
#include <pthread.h>

#include "controller.h"

int controller_destroy(runtime_t *data) {
  int code = 0;
  
  code = (data == NULL) * EFAULT;
  
  if (!code) {
    // Грубо, можно подождать и т.п.
    if (data->model) code = pthread_cancel(data->model);
    if (data->gui) code = pthread_cancel(data->gui);
    pthread_attr_destroy(&data->model_attr);
    pthread_attr_destroy(&data->gui_attr);
    pthread_condattr_destroy(&data->do_render_attr);
    pthread_cond_destroy(&data->do_render);
    pthread_condattr_destroy(&data->do_input_attr);
    pthread_cond_destroy(&data->do_input);
    pthread_mutexattr_destroy(&data->mutex_attr);
    pthread_mutex_destroy(&data->mutex);
  }

  return code;
}