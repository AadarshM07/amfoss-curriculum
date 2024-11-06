#include <ncurses.h>
#include <string.h>
#include "global.h"
#include "mode.h"




void init_modes() {
  global.modes[0] = (Mode){" NORMAL MODE", normal_mode};
  global.modes[1] = (Mode){" INSERT MODE", insert_mode};
  global.modes[2] = (Mode){"COMMAND MODE", command_mode};
  global.current_mode = global.modes[0];
}


      
void normal_mode(int ch) {
  // In normal mode:
  // - 'i' switches to insert mode
  switch (ch) {
  case 'i':
    global.current_mode = global.modes[1];
    break;
  case ':':
    getyx(stdscr, global.ret_y, global.ret_x);
    move(global.rows - 1, 0);
    clrtoeol();
    addch(':');
    memset(global.command_buf, 0, sizeof(global.command_buf));
    global.current_mode = global.modes[2];
    break;
  default:
    break;
  }
}

void highlight_syntax(char *line) {
      char *keywords[] = { "auto", "break", "case", "char", "const", "continue", "default",
                             "double", "else", "enum", "extern", "float", "for", "goto",
                            "if", "int", "long", "register", "return", "short", "signed", "sizeof",
                            "static", "struct", "switch", "typedef", "union", "unsigned", "void",
                            "volatile", "while","include", NULL};
      
      int current_position = 0; // Track the current position in the line

      while (line[current_position] != '\0') {
          // Check for the next keyword occurrence
          int nearest_pos = -1;  // Position of the nearest keyword
          char *next_keyword = NULL;

          for (int i = 0; keywords[i] != NULL; i++) {
              char *pos = strstr(line + current_position, keywords[i]);
              if (pos != NULL) {
                  if (nearest_pos == -1 || pos < (line + nearest_pos)) {
                      nearest_pos = pos - line;  // Update the nearest position
                      next_keyword = keywords[i]; // Update the next keyword
                  }
              }
          }

          if (next_keyword) {
              // Print text before the keyword
              mvprintw(0, current_position, "%.*s", nearest_pos - current_position, line + current_position);

              // Print the keyword in highlighted color
              int keyword_len = strlen(next_keyword);
              attron(COLOR_PAIR(1)); // Keyword color
              mvprintw(0, nearest_pos, "%s", next_keyword);
              attroff(COLOR_PAIR(1)); // Reset to default color

              // Update current position
              current_position = nearest_pos + keyword_len;
          } else {
              // If no more keywords, print the rest of the line
              mvprintw(0, current_position, "%s", line + current_position);
              break; // Exit the loop
          }
      }
}




char*search(const char *line, const char *seword) {
    int current_position = 0; // Track the current position in the line

    while (line[current_position] != '\0') {
        // Check for the next keyword occurrence
        char *pos = strstr(line + current_position, seword);
        int found=0;
        
        if (pos != NULL) {
            int nearest_pos = pos - line;  // Update the nearest position
            found=1;
            
            // Print up to the found keyword
            mvprintw(0, current_position, "%.*s", nearest_pos - current_position, line + current_position);
            

            attron(A_BOLD);  
            mvprintw(0, nearest_pos, "%s", seword);  
            attroff(A_BOLD);  

            current_position = nearest_pos + strlen(seword);
        } else {
            // If no more keywords, print the rest of the line
            mvprintw(0, current_position, "%s", line + current_position);
            break; // Exit the loop
        }
        if(found==0){
            return "search not found.";
        }else{
            return "search successfully found";

        }        
    }
    return "search not found";

}


void insert_mode(int ch) {
    int y, x;

    switch (ch) {
    case KEY_ESC:
        curs_set(2);
        global.current_mode = global.modes[0];
        break;
    case KEY_BACKSPACE:
        getyx(stdscr, y, x);
        move(y, x - 1);
        delch();
        global.file_buf[strlen(global.file_buf) - 1] = '\0';
        break;
    case KEY_LEFT:
        getyx(stdscr, y, x);
        move(y, x - 1);
        break;
    case KEY_RIGHT:
        getyx(stdscr, y, x);
        move(y, x + 1);
        break;
    case KEY_UP:
        getyx(stdscr, y, x);
        move(y - 1, x);
        break;
    case KEY_DOWN:
        getyx(stdscr, y, x);
        move(y + 1, x);
        break;
    default:
  
       if (strlen(global.file_buf) < sizeof(global.file_buf) - 1) {
                addch(ch);
                global.file_buf[strlen(global.file_buf)] = ch;
                global.file_buf[strlen(global.file_buf) + 1] = '\0'; // Null-terminate
            }
            // Call highlight_syntax with the current buffer
            highlight_syntax(global.file_buf);
            break;
  }
}


char *write_file_to_disk(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return "ERROR: Could not open file for writing.";
    }
    if (fwrite(global.file_buf, sizeof(char), strlen(global.file_buf), file) == 0) {
        fclose(file);
        return "ERROR: Could not write file to disk.";
    }
    fclose(file);
    return "INFO: File written to disk.";
}

char *read_file_from_disk(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return "ERROR: Could not open file for reading.";
    }
    memset(global.file_buf, 0, sizeof(global.file_buf));
    if (fread(global.file_buf, sizeof(char), sizeof(global.file_buf), file) == 0) {
        fclose(file);
        return "ERROR: Could not read file from disk.";
    }
    fclose(file);
    return "INFO: File read from disk.";
}


void handle_command(char *command_out, int buf_size) {
    char filename[256] = {0};  // Buffer for storing file name
    char searchh[256] ={0};
    // Check for "write" or "open" command with a file name
    if (sscanf(global.command_buf, "write %s", filename) == 1) {
        snprintf(command_out, buf_size, "%s", write_file_to_disk(filename));

    } else if (sscanf(global.command_buf,"search %s",searchh)==1){
        snprintf(command_out, buf_size,"%s",search(global.file_buf,searchh));
    } else if (sscanf(global.command_buf, "open %s", filename) == 1) {
        snprintf(command_out, buf_size, "%s", read_file_from_disk(filename));
        
        // Clear screen and print file contents to screen
        move(0,0);
        clear();
        printw("%s", global.file_buf);

        int y = 0, x = 0;
        for (size_t i = 0; i < strlen(global.file_buf); i++) {
            if (global.file_buf[i] == '\n') {
                y++;
                x = 0;
            } else {
                x++;
            }
        }
        global.ret_y = y;
        global.ret_x = x;
    } else if (strcmp(global.command_buf, "quit") == 0 || strcmp(global.command_buf, "q") == 0) {
        snprintf(command_out, buf_size, "Quitting editor.");
        global.running = false;
    } else if (strcmp(global.command_buf, "wq") == 0 || strcmp(global.command_buf, "writequit") == 0) {
        snprintf(command_out, buf_size, "%s", write_file_to_disk("filename.txt"));
        global.running = false;
    } else if (strcmp(global.command_buf, "help") == 0 || strcmp(global.command_buf, "h") == 0 || strcmp(global.command_buf, "?") == 0) {
        snprintf(command_out, buf_size, "Available commands: quit, write <filename>, open <filename>, clear , help ");
    
    }else if (strcmp(global.command_buf, "clear") == 0 || strcmp(global.command_buf, "c") == 0) { 
        clear();          // Clears the entire screen
        move(0, 0);       // Moves the cursor to the top-left corner
        refresh();  



    } else if (strcmp(global.command_buf, "") == 0) {
        // No output if no command is entered (just return to normal mode)
    } else {
        snprintf(command_out, buf_size, "ERROR: Command '%s' not found.", global.command_buf);
    }



#undef CMP_COMMANDS
#undef UNIMPLEMENTED
#undef CMP_COMMAND
#undef SET_COMMAND_OUT
}

void command_mode(int ch) {
  // In command mode:
  // - 'ESC' returns to normal mode
  // - 'BACKSPACE' deletes the previous character
  // - 'ENTER' executes the command
  // - Any other character is added to the command buffer
  int y, x;
  char command_out[256] = {0};

  switch (ch) {
  case KEY_RETURN:
    handle_command(command_out, sizeof(command_out));
    // fall through
  case KEY_ESC:
    move(global.rows - 1, 0);
    clrtoeol();
    if (strlen(command_out) > 0) {
      mvprintw(global.rows - 1, 0, "%s", command_out);
    }
    move(global.ret_y, global.ret_x);
    global.current_mode = global.modes[0];
    break;
  case KEY_BACKSPACE:
    if (strlen(global.command_buf) == 0) {
      break;
    }
    getyx(stdscr, y, x);
    move(y, x - 1);
    delch();
    global.command_buf[strlen(global.command_buf) - 1] = '\0';
    break;
  default:
    // Add character to command buffer
    if (strlen(global.command_buf) >= sizeof(global.command_buf) - 1) {
      // Buffer is full
      break;
    }
    global.command_buf[strlen(global.command_buf)] = ch;
    addch(ch);
    break;
  }
}