#include <stddef.h>
#include <errno.h>

#include "game_t.h"

int tetris_loop(game_t *game) {
    int code = 0;

    code = (game == NULL) * EFAULT;

    while (1) {
        // endless
    }
    
    return code;
}