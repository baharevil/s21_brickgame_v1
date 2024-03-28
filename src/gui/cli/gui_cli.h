#ifndef GUI_CLI_H
#define GUI_CLI_H

/*TODO:
GUI_CLI function here:
- Input
- Render
*/

int height = 20, width = 10;

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

void userInput(UserAction_t action, int hold);

#endif