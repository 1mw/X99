///
/// x99.c
/// X99 kernel entry.
///

#include <x99.h>
#include <xlib.h>
#include <memory/memory.h>
#include <memory/multiboot.h>
#include <shell.h>

void kernel_main(multiboot_info_t* mbt, unsigned int magic)
{
	/*
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
	*/

	// Temp main function for VGA testing
	xlib_memory_init(mbt, magic);
	xlib_vga_init(320, 200, 256);
	// xlib_vga_address[xlib_vga_width * 2 * 2] = 0x0e;

	int x, y;
	for(y = 0; y < 200; y++) {
		for(x = 0; x < 320; x++) {
			xlib_vga_address[xlib_vga_width * y + x] = (x % 2 == 0) ? 0x00 : 0x02;
		}
	}
}
