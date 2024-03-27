#ifndef CONROLLER_CLI_TETRIS_H
#define CONROLLER_CLI_TETRIS_H

#include "../../view/cli/cli.h"

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} game_info_t;

void * controller_loop( void * );
game_info_t update_current_state();

#endif