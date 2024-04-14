#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "common/game_info_t.h"

int game_info_destroy(game_info_t *game_info) {
  int code = 0;
  
  code = (game_info == NULL) * EINVAL;

  if (!code) {
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
      free(game_info->next);
      game_info->field = NULL;
    }
    free(game_info);
  }

  return code;
}