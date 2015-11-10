#include <shell.h>
#include <xlib.h>

void shell_init(void)
{
	// Allocate shell_command to be the maximum amount of characters that
	// xlib_io_getLine() can provide
	shell_command = malloc(sizeof(char) * 400);
}

void shell_start(void)
{
 	for(;;) {
		// TODO: After adding filesystem driver, display path here:
		xlib_video_writef("%r$ ");
		
		// Prompt user for shell_command
		*shell_command = 0;
		xlib_io_strcpy(shell_command, xlib_io_getLine());
		
		// Built in shell_commands
		if(xlib_io_strcmp(shell_command, "clear") == 0) {
			xlib_video_clearScreen();
			continue;
		}
		if(xlib_io_strcmp(shell_command, "exit") == 0) {
			shell_deinit();
			return;
		}
		
		// TODO: Add custom shell_commands/programs here
		xlib_video_writeString(shell_command);
		xlib_video_writeString(": command not found");
		xlib_video_newLine();
	}
}

void shell_deinit(void) {
	free(shell_command);
}