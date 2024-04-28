#include <errno.h>
#include <malloc.h>
#include <stddef.h>

#include "tetris.h"

int game_destroy(game_t *game) {
  if (!game) return EINVAL;

  int code = 0;

  game->figure_pos.x = 0;
  game->figure_pos.y = 0;
  game->last_op = 0;
  game->modified = 0;

  // Удаляем базу данных фигур
  if (game->database.figures) {
    code = figure_db_destroy(&game->database);
    game->database.count = 0;
  }

  // Удаляем текущую фигуру
  if (game->figure_cur) {
    figure_destroy(game->figure_cur);
  }

  if (game->game_info) {
    code = game_info_destroy(game->game_info);
  }

  free(game);

  return code;
}