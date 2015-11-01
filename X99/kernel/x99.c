// x99.c
//
// The main kernel file.

#include <x99.h>
#include <xlib.h>
#include <memory/memory.h>
#include <memory/multiboot.h>

void kernel_main(multiboot_info_t* mbt, unsigned int magic)
{
	// Write first message
	xlib_video_writef("%rX99             \n\n");
	
	// Initiate memory
	xlib_memory_init(mbt, magic);
	
	// Done
	
	int* a = malloc(sizeof(int));
	*a = 5;
	
	int* b = malloc(sizeof(int));
	*b = 12345;
	
	xlib_video_writeString("a -> 0x");
	xlib_video_writeString(xlib_misc_itoa((int) a, 16));
	xlib_video_newLine();
	
	xlib_video_writeString("*a -> ");
	xlib_video_writeString(xlib_misc_itoa(*a, 10));
	xlib_video_newLine();
	
	xlib_video_writeString("b -> 0x");
	xlib_video_writeString(xlib_misc_itoa((int) b, 16));
	xlib_video_newLine();
	
	xlib_video_writeString("*b -> ");
	xlib_video_writeString(xlib_misc_itoa(*b, 10));
	xlib_video_newLine();
	
	int tmp = *a;
	*a = *b;
	*b = tmp;
	
	xlib_video_writeString("a -> 0x");
	xlib_video_writeString(xlib_misc_itoa((int) a, 16));
	xlib_video_newLine();
	
	xlib_video_writeString("*a -> ");
	xlib_video_writeString(xlib_misc_itoa(*a, 10));
	xlib_video_newLine();
	
	xlib_video_writeString("b -> 0x");
	xlib_video_writeString(xlib_misc_itoa((int) b, 16));
	xlib_video_newLine();
	
	xlib_video_writeString("*b -> ");
	xlib_video_writeString(xlib_misc_itoa(*b, 10));
	xlib_video_newLine();
}
