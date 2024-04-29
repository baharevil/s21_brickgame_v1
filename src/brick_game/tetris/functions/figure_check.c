#include <errno.h>
#include <stddef.h>

#include "tetris.h"

int figure_check(game_t *game, enum direction dir) {
  if (!game) return EINVAL;

  int code = 0;

  for (int row = 0; !code && row < game->figure_cur->size; row++) {
    for (int col = 0; !code && col < game->figure_cur->size; col++) {
      if (game->figure_cur->body[row][col]) {
        // Проверка границ
        if (game->figure_pos.y + row +
                (dir == down) > field_height - 1
                || game->figure_pos.y + row -
                (dir == up) < 0
                || game->figure_pos.x + col -
                (dir == left) < 0
                || game->figure_pos.x + col +
                (dir == right) > field_width - 1)
          code = 1;

        // Проверка соседних блоков
        if (!code && game->game_info->field
                [game->figure_pos.y + row +
                (dir == down) - (dir == up)]
                [game->figure_pos.x + col +
                (dir == right) - (dir == left)] == 1)
          code = 1;
      }
    }
  }

  return code;
}