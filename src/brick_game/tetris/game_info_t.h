#ifndef GAME_INFO_T
#define GAME_INFO_T

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} game_info_t;

game_info_t update_current_state();

#endif