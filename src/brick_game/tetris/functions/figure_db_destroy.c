#include <stddef.h>
#include <errno.h>
#include <malloc.h>

#include "tetris.h"
#include "game_t.h"

int figure_db_destroy(figures_db *db) {
  int code = 0;

  code = (db == NULL) * EINVAL;
  
  if (!code) {
    for (unsigned i = 0; i < db->count; i++) {
      if (db->figures[i]) {
        figure_destroy(db->figures[i]);
        free(db->figures[i]);
        // db->figures[i] = NULL;
      }
    }
    free(db->figures);
  }

  return code;
}