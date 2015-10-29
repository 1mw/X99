// x99.c
//
// The main kernel file.

#include <x99.h>
#include <xlib.h>

void kernel_main()
{

    xlib_video_writeString("Please type something: ");
    char* input = xlib_io_getLine();

    xlib_video_newLine();
    xlib_video_writeString("You entered: ");
    xlib_video_writeString(input);
    /*
    while(1)
    xlib_video_writeString(xlib_misc_itoa(xlib_io_getScancode(), 16));*/
}
