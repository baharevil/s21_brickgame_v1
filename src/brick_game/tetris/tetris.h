#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>

#include "common/common.h"
#include "common/runtime_t.h"
#include "common/useraction_t.h"
#include "game_t.h"

typedef void (*action)(game_t *);

void *tetris_loop(runtime_t *);

// Геттер/сеттер адреса game
game_t *game_locate(game_t *);

int game_init(game_t **game);
int game_destroy(game_t *game);
int game_info_init(game_info_t **game_info);
int game_info_destroy(game_info_t *game_info);

figure_t *figure_create(const unsigned short size);
void figure_destroy(figure_t *figure);
figure_t *figure_load(FILE *file);
int figure_db_load(const char *dir, figures_db_t *db);
int figure_db_insert(figures_db_t *db, unsigned count);
int figure_db_destroy(figures_db_t *db);
int figure_copy(const figure_t *src, figure_t **dst);
int figure_copy_body(int **src, int **dst, unsigned short size);
int game_info_next_init(int ***next);
int game_info_next_destroy(int **next);
int figure_set(game_t *game);
int figure_unset(game_t *game);
int figure_rotate(game_t *game);

action fsm(fsm_state, UserAction_t);
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

void userInput(UserAction_t action, int hold);
game_info_t update_current_state();

#endif