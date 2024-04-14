#ifndef TETRIS_H
#define TETRIS_H

#include "common/common.h"
#include "common/runtime_t.h"
#include "common/useraction_t.h"
#include "game_t.h"

typedef void (*action)(game_t *);

void* tetris_loop(runtime_t *);

int game_init(game_t *);
int game_destroy(game_t *);
game_info_t * game_info_init();
int game_info_destroy(game_info_t *game_info);

void start_fn(game_t *);
void pause_fn(game_t *);
void spawn_fn(game_t *);
void move_fn(game_t *);
void shift_fn(game_t *);
void connect_fn(game_t *);
void game_over_fn(game_t *);
void terminate_fn(game_t *);
void left_fn(game_t *);
void right_fn(game_t *);
void up_fn(game_t *);
void down_fn(game_t *);
void action_fn(game_t *);

action fsm(fsm_state, UserAction_t);

// Геттер/сеттер адреса game
game_t * game_locate(game_t *);

figure * figure_create(const unsigned short size, const unsigned id);
void figure_destroy(figure *fig);

void userInput(UserAction_t action, int hold);

#endif