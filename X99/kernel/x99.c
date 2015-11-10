// x99.c
//
// The main kernel file.

#include <x99.h>
#include <xlib.h>
#include <memory/memory.h>
#include <memory/multiboot.h>
#include <xlang/xlang.h>
#include <shell.h>

void kernel_main(multiboot_info_t* mbt, unsigned int magic)
{
	// Write first message
	xlib_video_writef("%rX99             \n\n");
	
	// Initiate memory
	xlib_memory_init(mbt, magic);
	
	xlib_video_writeString("Press any key to continue...");
	xlib_io_getChar();
	
	xlib_video_clearScreen();
	
	shell_start();
	
	xlib_sys_panic("kernel :: Reached end of execution.");
}
