#include <stdio.h>

#include "tetris.h"

void start_fn(game_t *game) {
  if (game) {
    printf("Game started.\n");
    //Spawn()
    game->state = move;
  }
}

void pause_fn(game_t *game) {
  if (game) {
    static fsm_state temp_state = none;
    if (game->state != pause) {
      printf("Game paused.\n");
      temp_state = game->state;
      game->state = pause;
    } else {
      printf("Game unpaused.\n");
      game->state = temp_state;
    }
  }
}

void spawn_fn(game_t *game) {
  if (game)
  game->state = move;
}

void move_fn(game_t *game) {
  if (game)
  game->state = move;
//   TODO: conditions block
//   game->state = connect;
//   game->state = shift;
}

void shift_fn(game_t *game) {
  if (game)
  // shift()
  // push cond_variable
  game->state = move;
}

void connect_fn(game_t *game) {
  if (game)
  //connect()
  game->state = spawn;
}

void game_over_fn(game_t *game) {
  if (game)
  game->state = game_over;
}

void terminate_fn(game_t *game) {
  if (game)
  game_destroy(game);
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
