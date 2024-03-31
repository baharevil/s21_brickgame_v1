#include <stddef.h>
#include <errno.h>

#include "gui_cli.h"

int gui_cli_loop(pthread_cond_t *condition, pthread_mutex_t *mutex) {
    int code = 0;

    code = (condition == NULL || mutex == NULL) * EFAULT;

    while (1) {
        // endless
    }
    
    return code;
}