#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "tetris.h"

int game_destroy(game_t *game) {
  int code = 0;
  
  code = (game == NULL) * EINVAL;

  // Удаляем базу данных фигур
  if (!code && game->database.figures) {
    code = figure_db_destroy(&game->database);
    game->database.count = 0;
  }

  // Удаляем текущую фигуру
  if (!code && game->figure_cur) {
    figure_destroy(game->figure_cur);
  }

  if (!code && game->game_info) {
    game->game_info->score = 0;
    game->game_info->high_score = 0; // TODO: Close fd HISCORES
    game->game_info->level = 0;
    game->game_info->speed = 0;
    game->game_info->pause = 0;
    game->figure_pos.x = 0;
    game->figure_pos.y = 0;
    game->last_op = 0;
    game->modified = 0;
    code = game_info_destroy(game->game_info);
    free(game);
  }

  return code;
}