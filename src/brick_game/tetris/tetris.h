#ifndef TETRIS_H
#define TETRIS_H

#include "../../controller/controller.h"

#include "game_t.h"

int tetris_init(runtime_t *);
int tetris(game_t *);

// Точка входа потока
void* (*model_loop)(void*) = (void* (*)(void*))tetris_init;

#endif