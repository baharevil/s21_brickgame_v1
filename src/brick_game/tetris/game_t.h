/* Основная структура игры
Содержит все необходимые данные для выполнения модели
*/

#ifndef GAME_T_H
#define GAME_T_H

#ifndef GAME_INFO_T
#include "game_info_t.h"
#endif

typedef enum {
  start,
  pause,
  spawn,
  move,
  shift,
  connect,
  game_over
} fsm_state;

typedef struct {
  game_info_t *game_info;
  fsm_state state;
} game_t;


#endif