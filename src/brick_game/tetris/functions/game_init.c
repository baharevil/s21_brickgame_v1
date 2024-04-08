#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "tetris.h"

int game_init(game_t *game) {
  int code = 0;
  
  code = (game == NULL) * EINVAL;

  if (!code) {
    game_info_t *temp = calloc(1, sizeof(game_info_t));
    code = (temp == NULL) * ENOMEM;
    if (!code) game->game_info = temp;
  }

  if (!code) {
    int **temp = NULL;
    temp = (int **)malloc(field_height * sizeof(int *));
    code = (temp == NULL) * ENOMEM;
    if (!code) game->game_info->field = temp;
  }

  if (!code) {
    int *temp = NULL;
    for (int row = 0; !code && row < field_height; row++) {
      temp = (int *)malloc(field_width * sizeof(int));
      code = (temp == NULL) * ENOMEM;
      if (!code) game->game_info->field[row] = temp;
    }
    game->game_info->score = 0;
    game->game_info->high_score = 0; // TODO: Load HISCORES
    game->game_info->level = 1;
    game->game_info->speed = 100;
    game->game_info->pause = 0;

    game->figure_pos.x = 3;
    game->figure_pos.x = 0;

    game->state = start;
  }
  
  return code;
}