#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <stdio.h> // temporary

#include "useraction_t.h"

int get_action(UserAction_t *action, char *array) {
  int code = 0;
  UserAction_t result = {0};

  code = (action == NULL || array == NULL) * EINVAL;

  if (!code) {
    if (strcmp(array, "\033[A") == 0)
      { result = Up; printf("Up arrow\n"); }
    else if (strcmp(array, "\033[B") == 0)
      { result = Down; printf("Down arrow\n"); }
    else if (strcmp(array, "\033[C") == 0)
      { result = Right; printf("Right arrow\n"); }
    else if (strcmp(array, "\033[D") == 0)
      { result = Left; printf("Left arrow\n"); }
    else if (array[0] == ' ')
      { result = Action; printf("Action\n"); }
    else if (array[0] == 's')
      { result = Start; printf("Start\n"); }
    else if (array[0] == 'p')
      { result = Pause; printf("Pause\n"); }
    else if (array[0] == 'q')
      { result = Terminate; printf("Terminate\n"); }
    else
      printf("array: %s\n", array);
        
    *action = result;    
  }

  return code;
}
