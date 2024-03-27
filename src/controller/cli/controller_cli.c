#include <pthread.h>
#include <unistd.h>
#include <stddef.h>
#include <malloc.h>
#include <locale.h>
#include <stdint.h>

#include <stdio.h>

#include "controller_cli.h"

struct data {
  pthread_mutex_t mutex_lock;
  int value1;
};

int main() {
  int code = 0;  
  /* Все, что мы хотим отправить в поток, складываем в структуру,
  потому как операнд у функции создания потока только один */
  struct data data;

  data.value1 = 10;

  int value2 = 10;

  //инициализация исключающей блокировки
  pthread_mutex_init(&data.mutex_lock, NULL);

  pthread_t pthread0; /* идентификатор потока */
  pthread_attr_t attr; /* аттрибуты потока */

  /* получаем дефолтные значения атрибутов */
  pthread_attr_init(&attr);

  /* создаем новый поток */
  code = (pthread_create(&pthread0, &attr, controller_loop, (void *)&data) != 0);

  /* "Процесс завершается двумя путями - вызовом pthread_exit() или
   завершением потоковой функции. В случае, если процесс неотсоединен, то
   при его завершении ресурсы, выделенные процессу, не освобождаются до
   вызова pthread_join(). Если процесс отсоединенный - ресурсы
   освобождаются по ее завершению."  */

  /* ждем завершения исполнения потока */
  // ret_value = pthread_join(pthread0, NULL);

  // переводим в отсоединенный режим
  // pthread_detach(pthread0);

  while (value2)
  {
    printf("Main: %d\n", value2--);
    sleep(1);
  }

  //Удаляем исключающую блокировку
  pthread_mutex_destroy(&data.mutex_lock);

  // init ncurses
  // setlocale(LC_ALL, "");
  // initscr();

  // main API logic
  // controller_loop();

  // end ncurses
  // endwin();

  return code;
}

void * controller_loop(void *data) {
    // TODO Uptade_cerent_state
    // TODO user_input

  struct data *data0 = (struct data *)data;
  int num = data0->value1;
                       
  while (num)
  {
    /* No other thread is going to join() this one - прикольно, самоотсоединение:*/
    pthread_detach(pthread_self());

    // устанавливаем блокировку
    pthread_mutex_lock(&data0->mutex_lock);

    printf("Controller: %d\n", num--); // Операции ввода-вывода, изменение переменных, памяти.

    // снимаем блокировку
    pthread_mutex_unlock(&data0->mutex_lock);

    sleep(1);
  }
  pthread_exit(0);
}