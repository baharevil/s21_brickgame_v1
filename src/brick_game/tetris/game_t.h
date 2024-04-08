/* Основная структура игры
Содержит все необходимые данные для выполнения модели
*/

#ifndef GAME_T_H
#define GAME_T_H

#ifndef GAME_INFO_T
#include "game_info_t.h"
#endif

typedef struct position {
  int x;
  int y;
} position;

typedef enum fsm_state {
  none,
  start,
  pause,
  spawn,
  move,
  shift,
  connect,
  game_over
} fsm_state;

typedef struct game_t {
  game_info_t *game_info;
  position figure_pos;
  fsm_state state;
} game_t;


#endif