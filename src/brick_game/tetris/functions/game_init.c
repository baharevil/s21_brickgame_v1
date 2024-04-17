#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "tetris.h"

game_t * game_init() {
  int code = 0;
  game_t *game = NULL;
  
  game = calloc(1, sizeof(game_t));
  code = (game == NULL) * ENOMEM;

  // Инициализируем структуру game_info_t
  if (!code) {
    game_info_t *temp = NULL;
    temp = game_info_init();
    code = (temp == NULL) * ENOMEM;
    if (!code) game->game_info = temp;
  }

  // Инициализация массива фигур
  if (!code) {
    game->database.count = 0;
    game->database.figures = NULL;
    figure_db_load("./figures/", &game->database);
  }

  // Присваиваем первоначальные значения
  if (!code) {
    game->game_info->high_score = 0; // TODO: Load HISCORES
    game->game_info->level = 1;
    game->game_info->speed = 1000;
    game->game_info->pause = 0;

    game->figure_pos.x = 3;
    game->figure_pos.x = 0;

    game->state = start;
    game->last_op = time_msec();
    game->modified = false;
  }
  
  return game;
}