#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "game_t.h"

void figure_destroy(figure *fig) {
  int code = 0;
  
  code = (fig == NULL) * EINVAL;

  if (code) {
    for (int row = 0; row < fig->size; row++)
      if (fig->body[row]) free (fig->body[row]);
    if (fig->body) free(fig->body);
    if (fig) free(fig);
  }
}