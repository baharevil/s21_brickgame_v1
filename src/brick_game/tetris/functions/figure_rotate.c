#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "tetris.h"

int figure_rotate(game_t *game) {
  if (!game) return EINVAL;

  int code = 0;

  int **temp_body = NULL;
  temp_body = malloc(game->figure_cur->size * sizeof(int *));
  code = (temp_body == NULL) * ENOMEM;
  
  if (!code) {
    int *temp = NULL;
    for (int row = 0; !code && row < game->figure_cur->size; row++) {
      temp = calloc(game->figure_cur->size, sizeof(int));
      code = (temp == NULL) * ENOMEM;
      if (!code) temp_body[row] = temp;
    }
  }
// row
// 1 2  col
// 3 4

// row
//      col
//
  if (!code) {
    for (int col = 0; col < game->figure_cur->size; col++) {
      for (int row = game->figure_cur->size; row > 0; row--) {
        temp_body[col][row] = game->figure_cur->body[row][col];
      }
    }
  }

  figure_copy_body(temp_body, game->figure_cur->body, game->figure_cur->size);

  if (!code) {
    for (int row = 0; row < game->figure_cur->size; row++) {
      free(temp_body[row]);
    }
  }

  if (!code) free(temp_body);

  return code;
}