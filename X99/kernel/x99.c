///
/// x99.c
/// X99 kernel entry.
///

#include <x99.h>
#include <xlib.h>
#include <memory/memory.h>
#include <memory/multiboot.h>
// #include <xlang/xlang.h>
#include <shell.h>

void kernel_main(multiboot_info_t* mbt, unsigned int magic)
{
	// Write first message
	xlib_video_writef("%rX99 ");
	xlib_video_writeString("(Kernel was compiled at ");
	xlib_video_writeString(__TIME__);
	xlib_video_writeString(" on ");
	xlib_video_writeString(__DATE__);
	xlib_video_writeString(")\n\n");
	
	// Initiate memory
	xlib_memory_init(mbt, magic);
	
	xlib_video_writeString("Press any key to continue...");
	xlib_io_getChar();
	
	xlib_video_clearScreen();
	
	shell_start();
	
	xlib_sys_panic("kernel :: Reached end of execution.", __FILE__, __FUNCTION__, __LINE__);
}
