#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "tetris.h"
#include "game_t.h"

figure_t * figure_create(const unsigned short size) {
  int code = 0;
  figure_t *result = NULL;

  code = (size == 0) * EINVAL;

  if (!code) {
    figure_t * temp = NULL;
    temp = calloc(size, sizeof(figure_t));
    code = (temp == NULL) * ENOMEM;
    if (!code) result = temp;
  }

  if (!code) {
    result->size = size;
    int **temp_body = calloc(size, sizeof(int *));
    code = (temp_body == NULL) * ENOMEM;
    if (!code) result->body = temp_body;
  }

  if (!code) {
    int *temp = NULL;
    for (int row = 0; !code && row < size; row++) {
      temp = calloc(size, sizeof(int));
      code = (temp == NULL) * ENOMEM;
      if (!code) result->body[row] = temp;
    }
  }

  if (code && result) {
    figure_destroy(result);
    result = NULL;
  }

  return result;
}