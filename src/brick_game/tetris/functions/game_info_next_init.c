#include <errno.h>
#include <malloc.h>
#include <stddef.h>

#include "tetris.h"

int game_info_next_init(int ***next) {
  if (next == NULL) return EINVAL;

  int code = 0;

  // Аллоцируем строки next
  int **temp = NULL;
  temp = (int **)malloc(4 * sizeof(int *));
  code = (temp == NULL) * ENOMEM;
  if (!code) (*next) = temp;

  // Аллоцируем столбцы next
  if (!code) {
    int *temp = NULL;
    for (int row = 0; !code && row < 4; row++) {
      temp = (int *)malloc(4 * sizeof(int));
      code = (temp == NULL) * ENOMEM;
      if (!code) (*next)[row] = temp;
    }
  }

  return code;
}