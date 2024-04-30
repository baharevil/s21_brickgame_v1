#include <errno.h>
#include <string.h>

#include "tetris.h"

int game_info_clean(game_info_t *game_info) {
  if (!game_info) return EINVAL;

  int code = 0;

  game_info->high_score = 0;
  game_info->level = 1;
  game_info->speed = 1000;
  game_info->pause = 0;

  if (game_info->field) {
    for (int row = 0; row < field_height; row++) {
      memset(game_info->field[row], 0, field_width * sizeof(int));
    }
  }

  return code;
}