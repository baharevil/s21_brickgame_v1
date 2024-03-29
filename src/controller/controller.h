/*Модуль Контроллер.
Является точкой входа в программу.
Управляет потоками tetris и gui_cli.
Сам cli не имеет.
(Согласно README.md, ч.1)*/

#ifndef CONROLLER_H
#define CONROLLER_H

#include <pthread.h>

typedef struct {
  pthread_t model;
  pthread_t gui;
  pthread_attr_t model_attr;
  pthread_attr_t gui_attr;
  pthread_cond_t do_render;
  pthread_condattr_t do_render_attr;
  pthread_mutex_t mutex;
  pthread_mutexattr_t mutex_attr;
  int game_stop;
  int model_stop;
  int gui_stop;
} runtime_t;

int controller_init(runtime_t *);
int controller_init(runtime_t *);
void* controller_loop(void *);

#endif