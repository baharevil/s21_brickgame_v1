#ifndef TETRIS_H
#define TETRIS_H

#include "../../controller/controller.h"

#include "game_t.h"

int tetris_init(pthreads *);
int tetris(game_t *);


#endif