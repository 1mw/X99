#include <shell.h>
#include <xlib.h>
#include <memory/memory.h>
#include <types.h>

void shell_preserveBuffer(shell_buffer_t* buffer)
{
	for(int y = 0; y < xlib_video_MAX_ROW; y++) {
		for(int x = 0; x < xlib_video_MAX_COLUMN; x++) {
			char* v = (char*) (xlib_video_VIDEO_MEMORY + (((x * 80) + y) * 2));
			buffer->data[y * 80 + x] = *v;
			v++;
			buffer->formatting[y * xlib_video_MAX_COLUMN + x] = *v;
		}
	}
}

void shell_applyBuffer(shell_buffer_t* buffer)
{
	for(int y = 0; y < xlib_video_MAX_ROW; y++) {
		for(int x = 0; x < xlib_video_MAX_COLUMN; x++) {
			char* v = (char*) (xlib_video_VIDEO_MEMORY + (((xlib_video_row * 80) + xlib_video_column) * 2));
			*v++ = buffer->data[y * xlib_video_MAX_COLUMN + x];
			*v = buffer->formatting[y * xlib_video_MAX_COLUMN + x];
		}
	}
}

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
			shell_buffer_t* buffer = malloc(sizeof(shell_buffer_t));
			shell_preserveBuffer(buffer);
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
			shell_applyBuffer(buffer);
			free(buffer);
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