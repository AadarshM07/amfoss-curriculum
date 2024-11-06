#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#include "global.h"
#include "mode.h"

#include <ncurses.h>
#include <string.h>


void highlight_syntax(char *input);

int main() {
    // Declare variables
    int ch, y, x;
    // Initialize ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    set_escdelay(25);

    // Assuming init_global and init_modes initialize other aspects of your program
    init_global();
    init_modes();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK); // Set text color to cyan with default background

    while (global.running) {
        // Print mode in bottom right
        getyx(stdscr, y, x);
        mvprintw(global.rows - 2, global.cols - strlen(global.current_mode.name),
                 "%s", global.current_mode.name);
        move(y, x);

        ch = getch(); // Get user input
        global.current_mode.handler(ch);
        refresh();
    }
    
    endwin();
    return 0;

}