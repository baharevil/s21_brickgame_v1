#include <stdlib.h>

#include <ncurses.h>
#include <curses.h>
#include <locale.h>

#include <term.h>
#include <panel.h>
#include <signal.h>

int main () {
    setlocale(LC_ALL, "");
    
    // init 
    initscr();
    cbreak();
    noecho();
    
    // 
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    // stop
    refresh();
    
    // close and free
    endwin();
    exit_curses(0);
    
    // return 0;
    exit(0);
}
