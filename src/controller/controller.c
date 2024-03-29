#include <locale.h>
#include <pthread.h>
#include <stddef.h>

#include "controller.h"

int main() {
  int code = 0;

  runtime_t runtime = {0};
  extern void* (*model_loop)(void*);

  controller_init(&runtime);

  /* создаем новый поток */
  code = pthread_create(&runtime.model, &runtime.model_attr, model_loop, (void *)&runtime);


  return code;
}


