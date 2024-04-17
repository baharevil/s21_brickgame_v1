#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "tetris.h"
#include "game_t.h"

int figure_db_insert(figures_db *db, unsigned count) {
  int code = 0;

  code = (db == NULL) * EINVAL;
  
  if (!code) db->figures = realloc(db->figures, (count + 1)  * sizeof(figure*));

  code = (db->figures == NULL) * ENOMEM;

  return code;
}