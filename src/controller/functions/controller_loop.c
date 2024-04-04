#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#include <stdio.h>
#include <wchar.h>

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

  if (!code) {
    unsigned key = 0;
    canonical_mode(1);
    pthread_mutex_lock(&runtime->stdin_mutex);
    while (!runtime->game_stop) {
      key = getc(stdin);
        wprintf(L"key: %u\n", key);
      if (key == L'q') runtime->game_stop = 1;
    }
    pthread_mutex_unlock(&runtime->stdin_mutex);
    canonical_mode(0);
  }

  pthread_exit(0);
}
