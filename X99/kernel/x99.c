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
    xlib_video_writef("%rX99\n");

    // Initiate memory
    xlib_memory_init(mbt, magic);
}
