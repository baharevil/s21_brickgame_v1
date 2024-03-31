#include <stddef.h>
#include <pthread.h>
#include <unistd.h>

#include "controller.h"

int main() {
  int code = 0;

  runtime_t runtime = {0};
  // Model
  extern void* tetris_init(runtime_t *);
  void* (*model_init)(void*) = (void* (*)(void*))tetris_init;

  // GUI
  extern void* gui_cli_init(runtime_t *);
  void* (*gui_init)(void*) = (void* (*)(void*))gui_cli_init;

  code = controller_init(&runtime);

  if (!code) code = pthread_create(&runtime.model, &runtime.model_attr, model_init, (void *)&runtime);
  if (!code) code = pthread_create(&runtime.gui, &runtime.gui_attr, gui_init, (void *)&runtime);

  if (!code) {
    code = controller_loop(&runtime);
  }
  
  controller_destroy(&runtime);

  return code;
}


