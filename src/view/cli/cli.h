#ifndef CLI_H
#define CLI_H

#include <ncurses.h>
#include <term.h>
#include <panel.h>
#include <signal.h>
#include <curses.h>

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} user_action_t;

void user_input(user_action_t action, bool hold);

#endif