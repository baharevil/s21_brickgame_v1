//TODO: Инициализация и запуск основного цикла
#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <malloc.h>
#include <time.h>

#include "common/common.h"
#include "common/runtime_t.h"
#include "tetris.h"

void* tetris_loop(runtime_t *runtime) {
  int code = 0;

  code = (runtime == NULL) * EFAULT;
  
  if (!code) {
    pthread_t self_tid = pthread_self();
    pthread_detach(self_tid);
  }

  if (!code) {
    game_t *game = NULL;
    UserAction_t act = None;
    unsigned long now = 0;

    game = game_init();
    code = (game == NULL) * ENOMEM;
    if (!code) game_locate(game);

    while (!code && !atomic_load(&runtime->game_stop)) {
      // Цикл не грузит процессор
      thread_wait(100);

      // Вызов функции shift_fn по таймеру
      now = time_msec();
      if (game->state == move && now - game->last_op >= (unsigned long) game->game_info->speed) {
        shift_fn(game);
        game->last_op = now;
      }

      // Обработка пользовательского ввода
      if ((act = (UserAction_t)atomic_load(&runtime->msg_to_model)) > 0) {
        userInput(act, 0);
        atomic_store(&runtime->msg_to_model, 0);
        if (act == Terminate) atomic_store(&runtime->model_stop, 1);
      }
    }
    // Destroy the game
    game_destroy(game);
  }

  atomic_store(&runtime->model_stop, 1);

  pthread_barrier_wait(&runtime->barrier);

  pthread_exit(0);
}