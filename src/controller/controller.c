#include <stddef.h>
#include <pthread.h>
#include <unistd.h>

#include "controller.h"

int main() {
  int code = 0;
  runtime_t runtime = {0};

  // Model
  extern void* tetris_loop(runtime_t *);
  void* (*model_loop)(void*) = (void* (*)(void*))tetris_loop;

  // GUI
  extern void* gui_cli_loop(runtime_t *);
  void* (*gui_loop)(void*) = (void* (*)(void*))gui_cli_loop;

  // Controller
  void* (*input_controller)(void*) = (void* (*)(void*))controller_loop;

  code = controller_init(&runtime);

  if (!code) code = pthread_create(&runtime.model, &runtime.model_attr, model_loop, (void *)&runtime);
  if (!code) code = pthread_create(&runtime.gui, &runtime.gui_attr, gui_loop, (void *)&runtime);
  if (!code) code = pthread_create(&runtime.controller, &runtime.controller_attr, input_controller, (void *)&runtime);

  if (!code) {
    while (!atomic_load(&runtime.game_stop)) {
      sleep(1);
    }
    atomic_store(&runtime.model_stop, 1);
    atomic_store(&runtime.gui_stop, 1);
  }
  // TODO: Здесь должен быть потоковый барьер
  // sleep(1);
  
  controller_destroy(&runtime);

  return code;
}
