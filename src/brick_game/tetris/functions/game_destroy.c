#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "tetris.h"

int game_destroy(game_t *game) {
  int code = 0;
  
  code = (game == NULL || game->game_info == NULL) * EINVAL;

  if (!code) {
    // TODO: Free the database
    // free (game->database);
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