///
/// shell.h
/// The X99 shell specifications.
///

#ifndef shell_h
#define shell_h

#include <xlib.h>

///
/// A capture of the shell screen.
///
typedef struct shell_buffer {
	char data[80 * 25];
	char formatting[80 * 25];
	int x;
	int y;
} shell_buffer_t;

///
/// The last command that the user entered.
///
char* shell_command;

///
/// Function to start the shell.
///
void shell_start(void);

///
/// Function to initiate the shell.
///
void shell_init(void);

///
/// Function to deinit the shell. The commands in the shell should call this 
/// when they are going to exit the shell for any reason. This prevents memory 
/// leaks.
// 
void shell_deinit(void);

///
/// Captures the screen to the supplied buffer
///
void shell_preserveBuffer(shell_buffer_t* buffer);

///
/// Restores the screen from the supplied buffer.
///
void shell_applyBuffer(shell_buffer_t* buffer);

#endif