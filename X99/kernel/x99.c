// x99.c
//
// The main kernel file.

#include <x99.h>
#include <xlib.h>

void kernel_main()
{
    xlib_video_writef("%gHello, I am the computer. What is your name? ");
    char* name = xlib_io_getLine();
    xlib_video_writef("%gHello, ");
    xlib_video_writeString(name);
    xlib_video_newLine();

    xlib_video_writef("%gHow old are you? ");
    char* age = xlib_io_getLine();
    xlib_video_writef("%gI am ");
    xlib_video_writeString(age);
    xlib_video_writef("%g years old too!");
}
