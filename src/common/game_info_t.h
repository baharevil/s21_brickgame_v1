#ifndef GAME_INFO_T
#define GAME_INFO_T

enum field_size { field_height = 20, field_width = 10 };

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} game_info_t;

#endif