#include <stdlib.h>
#include <stdio.h>

#include "tetris.h"

void start_fn(game_t *game) {
  if (game) {
    game->state = start;
    // TODO: rand() from figures_database id/count
    // link game_info_t->next to figure in database
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
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}

void move_fn(game_t *game) {
  if (game) {
    game->state = move;
    game->last_op = time_msec();
  }
}

void shift_fn(game_t *game) {
  if (game) {
    fsm_state temp_state = game->state;
    game->state = shift;
    figure_unset(game);
    game->figure_pos.y++;
    figure_set(game);
    game->modified = true;
    game->state = temp_state;
    // TODO: check to connect
  }
}

void connect_fn(game_t *game) {
  if (game) {
    //connect()
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
  }
}

void left_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    game->figure_pos.x -= (game->figure_pos.x > 0);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}

void right_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    game->figure_pos.x += (game->figure_pos.x < field_width - game->figure_cur->size);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}
// It's a joke)
void up_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    game->figure_pos.y -= (game->figure_pos.y > 0);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}

void down_fn(game_t *game) {
  if (game)
    game->figure_pos.y += (game->figure_pos.y < field_height - game->figure_cur->size);
}

void action_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    figure_rotate(game);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}
