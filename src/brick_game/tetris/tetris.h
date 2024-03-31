#ifndef TETRIS_H
#define TETRIS_H

#include "../../controller/controller.h"

#include "game_t.h"

void * tetris_init(runtime_t *);
int tetris_loop(game_t *);

#endif