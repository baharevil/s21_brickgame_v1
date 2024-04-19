#include <stddef.h>
#include <errno.h>
#include <string.h>

#include "tetris.h"
#include "game_t.h"

int figure_copy(const figure_t *src, figure_t **dst) {
  int code = 0;

  code = (src == NULL) * EINVAL;

  if (!code) {
    if (*dst == NULL) {
      *dst = figure_create(src->size);
      figure_copy_body(src->body, (*dst)->body, src->size);
    } else if ((*dst)->size != src->size) {
      figure_destroy(*dst);
      *dst = figure_create(src->size);
      figure_copy_body(src->body, (*dst)->body, src->size);
    } else if ((*dst)->size == src->size) {
      figure_copy_body(src->body, (*dst)->body, src->size);
    }
  }

  return code;
}