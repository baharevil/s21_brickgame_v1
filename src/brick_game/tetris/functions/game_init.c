#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <stdlib.h>

#include "tetris.h"

int game_init(game_t **game) {
  int code = 0;
  code = (game == NULL) * EINVAL;

  *game = calloc(1, sizeof(game_t));
  code = (*game == NULL) * ENOMEM;

  // Инициализируем структуру game_info_t
  if (!code) {
    code = game_info_init(&(*game)->game_info);
  }

  // Инициализация массива фигур
  if (!code) {
    (*game)->database.figures = NULL;
    (*game)->database.count = 0;
    code = figure_db_load("./figures/", &(*game)->database);
    if (!code) code = ((*game)->database.count == 0) * ENODATA;
  }

  // Инициализация текущей игровой фигуры
  if (!code) {
    int rnd = rand() % ((*game)->database.count - 1);
    if (!code) code = game_info_next_init(&(*game)->game_info->next);
    if (!code)
      code = figure_copy_body((*game)->database.figures[rnd]->body,
                              (*game)->game_info->next,
                              (*game)->database.figures[rnd]->size);
    if (!code)
      code = figure_copy((*game)->database.figures[rnd], &(*game)->figure_cur);
  }

  // Присваиваем первоначальные значения
  if (!code) {
    (*game)->game_info->high_score = 0;  // TODO: Load HISCORES
    (*game)->game_info->level = 1;
    (*game)->game_info->speed = 1000;
    (*game)->game_info->pause = 0;

    (*game)->figure_pos.x = 3;
    (*game)->figure_pos.x = 0;

    (*game)->state = start;
    (*game)->last_op = time_msec();
    (*game)->modified = false;
  }

  return code;
}