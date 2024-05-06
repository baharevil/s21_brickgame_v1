#include <errno.h>
#include <malloc.h>
#include <stddef.h>

#include "common/game_info_t.h"
#include "tetris.h"

int game_info_destroy(game_info_t *game_info) {
  if (game_info == NULL) return EINVAL;

  int code = 0;

  if (game_info->field) {
    for (int row = 0; row < field_height; row++) {
      if (game_info->field[row]) {
        free(game_info->field[row]);
        game_info->field[row] = NULL;
      }
    }
    free(game_info->field);
    game_info->field = NULL;
  }

  if (game_info->next) {
    game_info_next_destroy(game_info->next);
    game_info->next = NULL;
  }

  game_info->score = 0;
  game_info->high_score = 0;  // TODO: Close fd HISCORES
  game_info->level = 0;
  game_info->speed = 0;
  game_info->pause = 0;

  free(game_info);

  return code;
}