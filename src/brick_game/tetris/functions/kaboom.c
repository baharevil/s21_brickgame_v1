#include <errno.h>
#include <malloc.h>
#include <string.h>

#include "tetris.h"

static int check_line_full(int *);
static int swap_lines_down(game_info_t *, int);

int kaboom(game_t *game) {
  if (!game) return EINVAL;

  int code = 0;

  for (int row = game->figure_pos.y; row < field_height; row++) {
    if (check_line_full(game->game_info->field[row])) {
      memset(game->game_info->field[row], 0, field_width * sizeof(int));
      swap_lines_down(game->game_info, row);
      game->game_info->score += 100;
      if (game->game_info->score % 600 > game->game_info->level) {
        game->game_info->level++;
        game->game_info->speed /= 2;
      }
    }
  }

  return code;
}

static int check_line_full(int *line) {
  if (!line) return 0;

  int code = 1;
  for (int col = 0; code && col < field_width; col++) {
    code = (line[col] == 1);
  }

  return code;
}

static int swap_lines_down(game_info_t *game_info, int row) {
  if (!game_info || !game_info->field || row < 1) return 1;

  int code = 0;
  int *temp_line = NULL;
  temp_line = calloc(field_width, sizeof(int));

  code = (temp_line == NULL) * ENOMEM;

  if (!code) {
    for (; row > 0; row--) {
      memcpy(temp_line, game_info->field[row], field_width * sizeof(int));
      memcpy(game_info->field[row], game_info->field[row - 1],
             field_width * sizeof(int));
      memcpy(game_info->field[row - 1], temp_line, field_width * sizeof(int));
    }
    free(temp_line);
  }

  return code;
}
