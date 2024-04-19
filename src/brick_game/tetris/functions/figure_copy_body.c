#include <stddef.h>
#include <errno.h>
#include <string.h>

#include "tetris.h"
#include "game_t.h"

int figure_copy_body(int **src, int **dst, unsigned short size) {
  int code = 0;

  code = (src == NULL || dst == NULL) * EINVAL;

  if (!code) {
    for (int row = 0; row < size; row++) {
      for (int col = 0; col < size; col++) {
        dst[row][col] = src[row][col];
      }
    }
  }

  return code;
}