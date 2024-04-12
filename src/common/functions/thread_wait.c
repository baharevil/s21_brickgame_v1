#include <stddef.h>
#include <pthread.h>
#include <sys/time.h>

int thread_wait(int time) {
  int code = 0;
  pthread_mutex_t mutex;
  pthread_cond_t condition;
  struct timespec how_much = {0};

  code = pthread_mutex_init(&mutex, NULL);
  if (!code) code = pthread_cond_init(&condition, NULL);

  if (!code) code = !timespec_get(&how_much, TIME_UTC);
  how_much.tv_nsec += time * CLOCKS_PER_SEC;
  
  if (!code) code = pthread_cond_timedwait(&condition, &mutex, &how_much);

  if (!code) code = pthread_mutex_destroy(&mutex);
  if (!code) code = pthread_cond_destroy(&condition);

  return code;
}