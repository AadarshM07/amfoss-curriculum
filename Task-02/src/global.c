#include <ncurses.h>
#include <string.h>
#include <stdlib.h> // For malloc and free

#include "global.h"

Global global = {0};

void init_global() {
  global.running = true;
  memset(global.command_buf, 0, sizeof(global.command_buf));

  // Allocate memory for file_name and copy a filename
  global.file_name = malloc(256);
  if (global.file_name != NULL) {
      strncpy(global.file_name, "filename.txt", 256);
  }

  memset(global.file_buf, 0, sizeof(global.file_buf));
  getmaxyx(stdscr, global.rows, global.cols);
}

// Don't forget to free file_name when the program ends
void cleanup_global() {
  free(global.file_name);
}
