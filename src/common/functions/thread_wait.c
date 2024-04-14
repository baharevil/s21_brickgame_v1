#include <stddef.h>
#include <pthread.h>
#include <sys/time.h>

int thread_wait(int msec) {
  int code = 0;
  pthread_mutex_t mutex;
  pthread_cond_t condition;
  struct timespec how_much = {0};

  code = pthread_mutex_init(&mutex, NULL);
  if (!code) code = pthread_cond_init(&condition, NULL);

  if (!code) code = !timespec_get(&how_much, TIME_UTC);

  if (!code) {
    long sec = msec / 100;
    msec -= sec * 100;
    long nsec = msec * 10000;
    how_much.tv_sec += sec;
    how_much.tv_nsec += nsec;
  }
  
  if (!code) {
    // pthread_mutex_lock(&mutex);
    code = pthread_cond_timedwait(&condition, &mutex, &how_much);
    // pthread_mutex_unlock(&mutex);
  }

  if (!code) code = pthread_mutex_destroy(&mutex);
  if (!code) code = pthread_cond_destroy(&condition);

  return code;
}