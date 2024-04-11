//TODO: Инициализация и запуск основного цикла
#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

#include "../../../controller/runtime_t.h"
#include "tetris.h"

void* tetris_loop(runtime_t *runtime) {
  int code = 0;

  code = (runtime == NULL) * EFAULT;
  
  if (!code) {
    pthread_t self_tid = pthread_self();
    // runtime->model = self_tid;
    
    /* No other thread is going to join() this one - прикольно,
    * самоотсоединение:*/
    pthread_detach(self_tid);
  }

  if (!code) {
    game_t game = {0};
    UserAction_t act = None;
    clock_t timer = 0, time_offset = 0;

    code = game_init(&game);
    
    if (!code)
      game_locate(&game);

    while (!code && !atomic_load(&runtime->game_stop)) {
      // Вызов функции shift_fn по таймеру
      code = ((time_offset = clock()) == -1) * ETIME;
      if (game.state == move && (time_offset - timer) / CLOCKS_PER_SEC >= game.game_info->speed / 20) {
        shift_fn(&game);
        timer = time_offset;
      }
      
      // Обработка пользовательского ввода
      if ((act = (UserAction_t)atomic_load(&runtime->msg_to_model)) > 0) {
        userInput(act, 0);
        atomic_store(&runtime->msg_to_model, 0);
        if (act == Terminate) atomic_store(&runtime->model_stop, 1);
      }
    }
  }

  atomic_store(&runtime->model_stop, 1);

  pthread_barrier_wait(&runtime->barrier);

  pthread_exit(0);
}