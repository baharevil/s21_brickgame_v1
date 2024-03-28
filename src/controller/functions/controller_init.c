#include <stddef.h>
#include <errno.h>
#include <pthread.h>

#include "controller.h"

int controller_init(pthreads *data) {
  int code = 0;
  
  code = (data == NULL) * EFAULT;
  
  if (!code) code = pthread_attr_init(&data->model_attr);
  if (!code) code = pthread_attr_init(&data->gui_attr);
  if (!code) code = pthread_condattr_init(&data->do_render_attr);
  if (!code) code = pthread_cond_init(&data->do_render, &data->do_render_attr);
  if (!code) code = pthread_mutexattr_init(&data->model_attr);
  if (!code) code = pthread_mutex_init(&data->mutex, &data->model_attr);

  return code;
}