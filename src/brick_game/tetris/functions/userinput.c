#include "tetris.h"

void userInput(UserAction_t user_action, int hold) {
  static game_t game;
  action act = NULL;
  
  // Если игра не инициализирована
  if (game.game_info == NULL)
    game_init(&game);
    
  // Получаем указатель на функцию-обработчик события
  act = fsm(game.state, user_action);

  if (hold) hold = 1;

  // Запускаем обработчик
  if (act) act(&game);
}
