#include <errno.h>
#include <stddef.h>

#include "tetris.h"

int figure_check(game_t *game, enum direction dir) {
  if (!game) return EINVAL;

  int code = 0;

  for (int row = 0; row < game->figure_cur->size; row++) {
    for (int col = 0; col < game->figure_cur->size; col++) {
      if (game->game_info->field
              [game->figure_pos.y + row +
               (dir == down && game->figure_pos.y + row + 1 < field_height) -
               (dir == up && game->figure_pos.y + row - 1 >= 0)]
              [game->figure_pos.x + col +
               (dir == right && game->figure_pos.x + col + 1 < field_width) -
               (dir == left && game->figure_pos.x + col - 1 >= 0)] == 1)
        code = 1;
    }
  }

  return code;
}