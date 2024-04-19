#include <stddef.h>
#include <errno.h>

#include "tetris.h"

int figure_set(game_t *game) {
  if(!game) return EINVAL;

  int code = 0;

  for (int row = 0; row < game->figure_cur->size; row++) {
    for (int col = 0; col < game->figure_cur->size; col++) {
      game->game_info->field[game->figure_pos.y + row][game->figure_pos.x + col] = \
      game->figure_cur->body[row][col];
    }
  }

  return code;
}