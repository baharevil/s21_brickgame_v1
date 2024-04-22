#include <stddef.h>

#include "game_t.h"

enum is_set { not_set = 0, set };

struct locate {
  game_t *addr;
  enum is_set value;
};

game_t *game_locate(game_t *game) {
  static struct locate location;
  game_t *result = NULL;

  if (game) {
    location.value = set;
    location.addr = game;
  }

  if (location.value == set && location.addr) result = location.addr;

  return result;
}