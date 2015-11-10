#include <shell.h>
#include <xlib.h>
#include <memory/memory.h>
#include <types.h>

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
		if(xlib_io_strcmp(shell_command, "pmem") == 0) {
			xlib_video_clearScreen();
			int i;
			for(i = 0; i < xlib_memory_numberOfEntries; i++) {
				xlib_video_writeLinef("%gpmem");
				xlib_video_writeString("Entry #");
				xlib_video_writeString(xlib_misc_itoa(i, 10));
				xlib_video_newLine();
				xlib_video_writef("    %rstart%n -> 0x");
				xlib_video_writeString(xlib_misc_itoa(xlib_memory_mmapStarts[i], 16));
				xlib_video_newLine();
				
				xlib_video_writef("    %rend%n -> 0x");
				xlib_video_writeString(xlib_misc_itoa(xlib_memory_mmapEnds[i], 16));
				xlib_video_newLine();
				
				xlib_video_writef("    %rlength%n -> 0x");
				xlib_video_writeString(xlib_misc_itoa(xlib_memory_mmapLength[i], 16));
				xlib_video_newLine();
				
				xlib_video_writef("    %rtype%n -> 0x");
				xlib_video_writeString(xlib_misc_itoa(xlib_memory_mmapType[i], 16));
				xlib_video_newLine();
				
				xlib_video_writef("Press any key to display next entry...");
				xlib_io_getChar();
				xlib_video_clearScreen();
			}
			continue;
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