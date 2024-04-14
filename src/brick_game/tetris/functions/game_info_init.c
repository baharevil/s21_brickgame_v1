#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "tetris.h"

game_info_t * game_info_init() {
  int code = 0;

  game_info_t *game_info = NULL;

  // Аллоцируем структуру game_info_t
  game_info_t *temp = calloc(1, sizeof(game_info_t));
  code = (temp == NULL) * ENOMEM;
  if (!code) game_info = temp;

  // Аллоцируем строки поля
  if (!code) {
    int **temp = NULL;
    temp = (int **)malloc(field_height * sizeof(int *));
    code = (temp == NULL) * ENOMEM;
    if (!code) game_info->field = temp;
  }
  // Аллоцируем столбцы поля
  if (!code) {
    int *temp = NULL;
    for (int row = 0; !code && row < field_height; row++) {
      temp = (int *)malloc(field_width * sizeof(int));
      code = (temp == NULL) * ENOMEM;
      if (!code) game_info->field[row] = temp;
    }
  }

  if (code)
    game_info_destroy(game_info);

  return game_info;
}