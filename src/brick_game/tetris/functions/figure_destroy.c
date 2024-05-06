#include <errno.h>
#include <malloc.h>
#include <stddef.h>

#include "game_t.h"

int figure_destroy(figure_t *figure) {
  int code = 0;

  code = (figure == NULL) * EINVAL;

  if (!code) {
    for (int row = 0; row < figure->size; row++)
      if (figure->body[row]) free(figure->body[row]);
    if (figure->body) free(figure->body);
    figure->id = 0;
    figure->size = 0;
    free(figure);
  }

  return code;
}