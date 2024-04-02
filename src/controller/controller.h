/*Модуль Контроллер.
Является точкой входа в программу.
Управляет потоками tetris и gui_cli.
Сам cli не имеет.
(Согласно README.md, ч.1)*/

#ifndef CONROLLER_H
#define CONROLLER_H

#include "runtime_t.h"

int controller_init(runtime_t *);
void* controller_loop(runtime_t *);
int controller_destroy(runtime_t *);

#endif