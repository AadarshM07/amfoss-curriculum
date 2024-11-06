#pragma once 

// Key definitions for modes
#define KEY_ESC 27      // Escape key
#define KEY_RETURN 10   // Enter/Return key
#define KEY_LEFTARROW 37
#define KEY_RIGHTARROW 39
#define CTRL_C 3
#define CTRL_Z 26
#define CTRL_Y 25
#define MAX_BUFFER_SIZE 1024
#define MAX_LENGTH 256


typedef struct mode {
    char *name;                          // Name of the mode
    void (*handler)(int ch);            // Function pointer to the mode handler
} Mode;


// Function prototypes for initializing and handling modes
void init_modes();
void normal_mode(int ch);
void insert_mode(int ch);
void command_mode(int ch);
