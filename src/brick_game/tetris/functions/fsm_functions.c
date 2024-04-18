#include <stdio.h>

#include "tetris.h"

void start_fn(game_t *game) {
  if (game) {
    game->state = start;
    // TODO: rand() from figures_database id/count
    // link game_info_t->next to figure in database
    printf("Game started.\n");
    game->last_op = time_msec();
    spawn_fn(game);
  }
}

void pause_fn(game_t *game) {
  if (game) {
    static fsm_state temp_state;
    if (game->game_info->pause) {
      game->state = temp_state;
      game->game_info->pause = 0;
      game->last_op = time_msec();
      printf("Game unpaused.\n");
    } else {
      temp_state = game->state;
      game->game_info->pause = 1;
      game->state = pause;
      printf("Game paused.\n");
    }
  }
}

void spawn_fn(game_t *game) {
  if (game) {
    game->state = spawn;
    // spawn()
    move_fn(game);
  }
}

void move_fn(game_t *game) {
  if (game)
  game->state = move;
  game->last_op = time_msec();
//   TODO: conditions block
//   game->state = connect;
}

void shift_fn(game_t *game) {
  if (game) {
    fsm_state temp_state = game->state;
    game->state = shift;
    printf("Shifted.\n");
    // shift()
    // push cond_variable
    game->modified = true;
    game->state = temp_state;
  }
}

void connect_fn(game_t *game) {
  if (game)
  //connect()
  spawn_fn(game);
}

void game_over_fn(game_t *game) {
  if (game)
  game->state = game_over;
}

void terminate_fn(game_t *game) {
  if (game) {
    game->state = none;
  }
}

void left_fn(game_t *game) {
  if (game)
    game->figure_pos.x -= (game->figure_pos.x > 0);
}

void right_fn(game_t *game) {
  if (game)
    game->figure_pos.x += (game->figure_pos.x < field_width - 4);
}

void up_fn(game_t *game) {
  if (game)
    game->figure_pos.x -= (game->figure_pos.y > 0);
}

void down_fn(game_t *game) {
  if (game)
    game->figure_pos.x += (game->figure_pos.y < field_height - 4);
}

void action_fn(game_t *game) {
  if (game)
    // rotate()
    game->figure_pos.y = 0; // Заглушка
}
