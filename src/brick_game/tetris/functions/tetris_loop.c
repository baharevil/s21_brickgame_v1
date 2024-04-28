// TODO: Инициализация и запуск основного цикла
#include <errno.h>
#include <malloc.h>
#include <pthread.h>
#include <stddef.h>
#include <time.h>

#include "common/common.h"
#include "common/runtime_t.h"
#include "tetris.h"

void *tetris_loop(runtime_t *runtime) {
  int code = 0;
  game_t *game = NULL;

  code = (runtime == NULL) * EFAULT;

  // if (!code) {
  //   pthread_t self_tid = pthread_self();
  //   pthread_detach(self_tid);
  // }

  if (!code) {
    UserAction_t act = None;
    unsigned long now = 0;

    code = game_init(&game);

    if (!code) {
      signals_block();
      game_locate(game);
    }

    while (!code && !atomic_load(&runtime->game_stop)) {
      // Цикл не грузит процессор
      thread_wait(100);

      // Проверяем, не завершает ли модель игру
      if (game->state == none) {
        game_locate(game);
        atomic_store(&runtime->model_stop, 1);
        pthread_cond_signal(&runtime->do_render);
      }

      // Вызов функции shift_fn по таймеру
      now = time_msec();
      if (game->state == moving &&
          now - game->last_op >= (unsigned long)game->game_info->speed) {
        shift_fn(game);
        game->last_op = now;
      }

      // Обработка пользовательского ввода
      if (game->state &&
          (act = (UserAction_t)atomic_load(&runtime->msg_to_model)) > 0) {
        userInput(act, 0);
        atomic_store(&runtime->msg_to_model, 0);
      }

      if (game->modified) {
        game->modified = false;
        pthread_cond_signal(&runtime->do_render);
      }
    }
  }

  // Destroy the game
  if (game) game_destroy(game);

  atomic_store(&runtime->model_stop, 1);

  pthread_barrier_wait(&runtime->barrier);

  pthread_exit(0);
}