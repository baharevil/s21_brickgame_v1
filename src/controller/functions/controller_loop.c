#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <poll.h>

#include <stdio.h>
#include <wchar.h>
#include <string.h>

#include "controller.h"

void* controller_loop(runtime_t *runtime) {
  int code = 0;

  code = (runtime == NULL) * EFAULT;
  
  if (!code) {
    pthread_t self_tid = pthread_self();
    runtime->controller = self_tid;
    
    /* No other thread is going to join() this one - прикольно,
    * самоотсоединение:*/
    code = pthread_detach(self_tid);
  }

  if (!code) code = canonical_mode(1);

  if (!code) {
    char key[4] = {0};
    int len = 0;
    UserAction_t action = 0;
    int poll_code = 0;
    struct pollfd event = {0};
    event.events = POLLIN;
    event.fd = STDIN_FILENO;
    
    // Основной цикл
    pthread_mutex_lock(&runtime->stdin_mutex);
    while (!code && !atomic_load(&runtime->game_stop)) {
      poll_code = poll(&event, 1, -1);
      if (poll_code > 0 && event.revents & POLLIN) {
        event.revents = 0;
        len = read(STDIN_FILENO, key, 4);
        key[len] = 0;
        code = get_action(&action, key);
        if (!code && action) atomic_store(&runtime->msg_to_model, (int)action);
        if (action == Terminate) atomic_store(&runtime->game_stop, 1);
      } else {
        atomic_store(&runtime->gui_stop, 1);
      }
    }
    pthread_mutex_unlock(&runtime->stdin_mutex);
    canonical_mode(0);
  }

  pthread_exit(0);
}
