#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "tetris.h"

int game_destroy(game_t *game) {
  int code = 0;
  
  code = (game == NULL || game->game_info == NULL) * EINVAL;

  if (!code) {
    if (game->game_info->field) {
      for (int row = 0; !code && row < field_height; row++) {
        if (game->game_info->field[row]) {
          free(game->game_info->field[row]);
          game->game_info->field[row] = NULL;
        }
      }
      free(game->game_info->field);
      game->game_info->field = NULL;
    }
    
    if (game->game_info->next) {
      free(game->game_info->next);
      game->game_info->field = NULL;
    }
    
    game->game_info->score = 0;
    game->game_info->high_score = 0; // TODO: Close fd HISCORES
    game->game_info->level = 0;
    game->game_info->speed = 0;
    game->game_info->pause = 0;
    free(game->game_info);

    game->state = 0;
  }

  return code;
}