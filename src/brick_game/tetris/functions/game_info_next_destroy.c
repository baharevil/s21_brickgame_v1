#include <errno.h>
#include <malloc.h>
#include <stddef.h>

#include "tetris.h"

enum { present = -1, not_present = -2 };

int game_info_next_destroy(int **next) {
  if (!next) return EINVAL;

  int code = 0;

  for (int row = 0; !code && row < 4; row++) {
    free(next[row]);
  }

  free(next);

  return code;
}