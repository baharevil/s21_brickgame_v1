#include <stdio.h>
#include <stdlib.h>

#include "tetris.h"

void start_fn(game_t *game) {
  if (game) {
    game->state = start;
    // game->last_op = time_msec();
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
    } else {
      temp_state = game->state;
      game->game_info->pause = 1;
      game->state = pause;
    }
  }
}

void spawn_fn(game_t *game) {
  if (game) {
    game->state = spawn;
    int rnd = rand() % (game->database.count - 1);
    figure_copy(game->database.figures[rnd], &game->figure_cur);
    game->figure_pos.x = field_width / 2 - game->figure_cur->size / 2;
    game->figure_pos.y = 0;
    figure_set(game);
    game->last_op = time_msec();
    game->modified = true;
    move_fn(game);
  }
}

void move_fn(game_t *game) {
  if (game) {
    game->state = moving;
  }
}

void shift_fn(game_t *game) {
  if (game) {
    fsm_state temp_state = game->state;
    game->state = shift;
    figure_unset(game);
    // check to connect
    if (figure_check(game, down) != 0) connect_fn(game);
    else game->figure_pos.y++;
    figure_set(game);
    game->last_op = time_msec();
    game->modified = true;
    game->state = temp_state;
  }
}

void connect_fn(game_t *game) {
  if (game) {
    game->state = connect;
    figure_set(game);
    spawn_fn(game);
  }
}

void game_over_fn(game_t *game) {
  if (game) {
    // Game Over screen, Start to Play again
    game->state = game_over;
  }
}

void terminate_fn(game_t *game) {
  if (game) {
    game->state = none;
    game_locate(game);
  }
}

void left_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    game->figure_pos.x -= !figure_check(game, left);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}

void right_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    game->figure_pos.x += !figure_check(game, right);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}
// It's a joke)
void up_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    game->figure_pos.y -= !figure_check(game, up);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}

void down_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    game->figure_pos.y += !figure_check(game, down);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}

void action_fn(game_t *game) {
  if (game) {
    int check = 0;
    figure_t *temp = NULL;
    temp = figure_create(game->figure_cur->size);
    figure_copy_body(game->figure_cur->body, temp->body, game->figure_cur->size);
    figure_unset(game);
    figure_rotate(game);
    check = figure_check(game, up) || figure_check(game, down) || figure_check(game, left) || figure_check(game, right);
    if (check) {
      figure_copy_body(temp->body, game->figure_cur->body, game->figure_cur->size);
    }
    figure_set(game);
    figure_destroy(temp);
    game->modified = true;
    move_fn(game);
  }
}
