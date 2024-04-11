#include <time.h>

#include "tetris.h"

void userInput(UserAction_t user_action, int hold) {
  int code = 0;
  action act = NULL;

  game_t *game = game_locate(NULL);

  code = (game == NULL);
  
  if (!code) {
    // Получаем указатель на функцию-обработчик события
    act = fsm(game->state, user_action);

    // Заглушка
    if (hold) hold = 1;

    // Запускаем обработчик
    if (act) act(game);
  }
}
