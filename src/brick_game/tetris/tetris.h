#ifndef TETRIS_H
#define TETRIS_H

#include "../../controller/controller.h"
#include "../../controller/useraction_t.h"

#include "game_t.h"

void * tetris_loop(runtime_t *);

void userInput(UserAction_t action, int hold);

#endif