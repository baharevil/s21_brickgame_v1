#ifndef RUNTIME_T
#define RUNTIME_T

#include <stdbool.h>
#include <pthread.h>

typedef struct {
  pthread_t model;
  pthread_t gui;
  pthread_attr_t model_attr;
  pthread_attr_t gui_attr;
  pthread_cond_t do_render;
  pthread_condattr_t do_render_attr;
  pthread_cond_t do_input;
  pthread_condattr_t do_input_attr;
  pthread_mutex_t mutex;
  pthread_mutexattr_t mutex_attr;
  bool game_stop;
  bool model_stop;
  bool gui_stop;
} runtime_t;

#endif