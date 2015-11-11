// X99 Shell

#ifndef shell_h
#define shell_h

#include <xlib.h>

typedef struct shell_buffer {
	char data[80 * 25];
	char formatting[80 * 25];
} shell_buffer_t;

char* shell_command;

void shell_start(void);
void shell_init(void);

// The commands in the shell should call this when they are going to exit the
// shell for some reason. This prevents memory leaks.
void shell_deinit(void);

void shell_preserveBuffer(shell_buffer_t* buffer);
void shell_applyBuffer(shell_buffer_t* buffer);

#endif