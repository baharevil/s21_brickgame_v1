/*Модуль Контроллер.
Является точкой входа в программу.
Управляет потоками tetris и gui_cli.
Сам cli не имеет.
(Согласно README.md, ч.1)*/

#ifndef CONROLLER_H
#define CONROLLER_H

#include <pthread.h>

typedef struct {
  pthread_t *tetris;
  pthread_t *gui;
} threads;

void *controller_loop(void *);

#endif