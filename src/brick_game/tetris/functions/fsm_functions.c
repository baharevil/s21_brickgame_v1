#include <stdio.h>
#include <stdlib.h>

#include "tetris.h"

void start_fn(game_t *game) {
  if (game) {
    game_info_clean(game->game_info);
    game->state = start;
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
    // Spawn next figure & choose new random
    figure_copy(game->database.figures[game->next_id], &game->figure_cur);
    game->next_id = rand() % (game->database.count - 1);
    game_info_next_clean(game->game_info->next);
    figure_copy_body(game->database.figures[game->next_id]->body,
                     game->game_info->next,
                     game->database.figures[game->next_id]->size);

    game->figure_pos.x = field_width / 2 - game->figure_cur->size / 2;
    game->figure_pos.y = 0;
    if (figure_check(game))
      game_over_fn(game);
    else {
      figure_set(game);
      game->last_op = time_msec();
      game->modified = true;
      move_fn(game);
    }
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
    game->figure_pos.y += 1;
    if (figure_check(game)) {
      game->figure_pos.y -= 1;
      connect_fn(game);
    } else if (game->state != game_over) {
      figure_set(game);
      game->last_op = time_msec();
      game->state = temp_state;
    }
    game->modified = true;
  }
}

void connect_fn(game_t *game) {
  if (game) {
    game->state = connect;
    figure_set(game);
    kaboom(game);
    spawn_fn(game);
  }
}

void game_over_fn(game_t *game) {
  if (game) {
    game->state = game_over;
    logo_game_over(game->game_info->field);
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
    game->figure_pos.x -= 1;
    game->figure_pos.x += figure_check(game);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}

void right_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    game->figure_pos.x += 1;
    game->figure_pos.x -= figure_check(game);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}
// It's a joke)
void up_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    game->figure_pos.y -= 1;
    game->figure_pos.y += figure_check(game);
    figure_set(game);
    game->modified = true;
    move_fn(game);
  }
}

void down_fn(game_t *game) {
  if (game) {
    figure_unset(game);
    game->figure_pos.y += 1;
    game->figure_pos.y -= figure_check(game);
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
    if (temp) {
      figure_copy_body(game->figure_cur->body, temp->body,
                       game->figure_cur->size);
      figure_unset(game);
      figure_rotate(game);
      check = figure_check(game);
      if (check) {
        figure_copy_body(temp->body, game->figure_cur->body,
                         game->figure_cur->size);
      }
      figure_destroy(temp);
      figure_set(game);
      game->modified = true;
    }
    move_fn(game);
  }
}
