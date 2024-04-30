#include <errno.h>
#include <malloc.h>
#include <stddef.h>

#include "tetris.h"

int figure_rotate(game_t *game) {
  if (!game) return EINVAL;

  int code = 0;

  // int **temp_body = NULL;
  figure_t *temp = NULL;
  temp = figure_create(game->figure_cur->size);
  code = (temp == NULL) * ENOMEM;

  if (!code) {
    for (int col = 0; col < game->figure_cur->size; col++) {
      for (int row = game->figure_cur->size - 1, row_n = 0; row >= 0; row--, row_n++) {
        temp->body[col][row_n] = game->figure_cur->body[row][col];
      }
    }
  }

  figure_copy_body(temp->body, game->figure_cur->body, game->figure_cur->size);

  if (!code) {
    figure_destroy(temp);
    // for (int row = 0; row < game->figure_cur->size; row++) {
    //   free(temp_body[row]);
    // }
  }

  // if (!code) free(temp_body);

  return code;
}