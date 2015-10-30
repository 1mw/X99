// xlib.c
//
// The implementation of xlib, the standard library for X99.

#include <xlib.h>
#include <types.h>

///
/// xlib_video
///

int xlib_video_column = 0;
int xlib_video_row = 0;

void xlib_video_writeString(const char* string)
{
    while(*string != 0) {
		char* v = (char*) (xlib_video_VIDEO_MEMORY + (((xlib_video_row * 80) + xlib_video_column) * 2));
		*v = *string;
		xlib_video_column++;

		if(xlib_video_column >= xlib_video_MAX_COLUMN)
		{
			xlib_video_newLine();
		}

		string++;
	}
}

void xlib_video_writef(const char* formattedString)
{
    int color = 0;
    while(*formattedString != 0) {
        char* v = (char*) (xlib_video_VIDEO_MEMORY + (((xlib_video_row * 80) + xlib_video_column) * 2));
        if(*formattedString != '%') {
            *v++ = *formattedString;
            if(color != 0)
                *v = color;

            xlib_video_column++;

            if(xlib_video_column >= xlib_video_MAX_COLUMN)
                xlib_video_newLine();

            formattedString++;
        } else {
            switch(*(formattedString + 1)) {
                case 'g':
                    color = 0x0a;
                    break;
                case 'b':
                    color = 0x09;
                    break;
                case 'w':
                    color = 0x0f;
                    break;
                case 'c':
                    color = 0x0b;
                    break;
                case 'r':
                    color = 0x0c;
                    break;
                case 'm':
                    color = 0x0d;
                    break;
                case 'y':
                    color = 0x0e;
                    break;
                // Reset
                case 'n':
                    color = 0x07;
                    break;
            }

            formattedString += 2;
        }
    }
}

void xlib_video_newLine()
{
    xlib_video_column = 0;
    xlib_video_row++;

    if(xlib_video_row > xlib_video_MAX_ROW) {
        xlib_video_row = 0;
    }
}

///
/// end xlib_video
///

///
/// xlib_io
///
bool shiftKeyIsDown = false;

char xlib_io_getScancode()
{
    return xlib_io_inb(0x60);
}

unsigned int xlib_io_getAndAnalyzeScancode()
{
    unsigned int scancode;
    while(1) {
        // Wait for the keyboard to tell us that there is a key pressed
        while(!(xlib_io_inb(0x64) & 1));

        scancode = xlib_io_getScancode();

        if (((scancode&0x7f) == 0x2a) || ((scancode&0x7f) == 0x36)) {
    		/*
    		 * Next key may use shift table
    		 */
    		if ((scancode & 0x80) == 0) {
    			shiftKeyIsDown = true;
                continue;
    		} else {
    			shiftKeyIsDown = false;
                continue;
            }

    	}

        // To check if a key is released, check bit 7 of scan code
        if(scancode & 0x80) {
            // Bitmask 8th and more bits to compare just the key (not also the
            // 7th bit indicating whether or not its a release code).
            scancode &= 0x7F;

            continue;
        }

        // TODO: Check for shift keys
        return scancode;
    }
}

char xlib_io_getChar()
{
    unsigned int scan;
    unsigned char retchar;
    scan = xlib_io_getAndAnalyzeScancode();

    if(shiftKeyIsDown) {
        retchar = xlib_io_asciiShift[scan];
    } else {
        retchar = xlib_io_asciiNonShift[scan];
    }

    return retchar;
}

// Returns a max of 400 characters
char* xlib_io_getLine()
{
    int startPos = xlib_video_row * 80 + xlib_video_column;
    char buf[400] = {0};
    int bufPos = 0;

    while(1) {
        char c = xlib_io_getChar();
        switch(c) {
            case '\b': {
                if(xlib_video_row * 80 + xlib_video_column > startPos) {
                    if(xlib_video_column == 0) {
                        xlib_video_column = xlib_video_MAX_COLUMN - 1;
                        xlib_video_row--;
                        xlib_video_writeString(" ");

                        xlib_video_column = xlib_video_MAX_COLUMN - 1;
                        xlib_video_row--;

                        buf[bufPos] = 0;
                        buf[bufPos + 1] = 0;
                        bufPos -= 2;
                    } else {
                        xlib_video_column--;
                        xlib_video_writeString(" ");
                        xlib_video_column--;

                        buf[bufPos] = 0;
                        bufPos--;
                    }
                }
                break;
            }

            case '\n': {
                xlib_video_newLine();
                return &buf[0];
            }

            default: {
                // Use temporary value to print because xlib_video_writeString
                // is expecting a null-terminated-string.
                char tmp[2];
                tmp[0] = c;
                tmp[1] = 0;

                xlib_video_writeString(&tmp[0]);
                buf[bufPos] = c;
                bufPos++;
                break;
            }
        }
    }
}
///
/// end xlib_io
///

///
/// xlib_misc
///

char* xlib_misc_itoa(int val, int base)
{
    if(val == 0)
        return "0";

    static char buf[32] = {0};
    int i = 30;

    for(; val && i; i--, val /= base) {
        buf[i] = "0123456789abcedf"[val % base];
    }

    return &buf[i + 1];
}

///
/// end xlib_misc
///

///
/// xlib_sys
///
void xlib_sys_panic(char* message)
{
    // Tell user that we panicked and why
    xlib_video_newLine();
    xlib_video_writef("%rPANIC: ");
    xlib_video_writef(message);

    // Hang
    while(1);
}

///
/// end xlib_sys
///

///
/// xlib memory functions (no prefix because of how common they are)
///
unsigned long last = 0;

void* malloc(int size);

///
/// end xlib memory functions
///

///
/// xlib_math
///

int xlib_math_floor(double x)
{
    int xi = (int)x;
    return x < xi ? xi - 1 : xi;
}

///
/// end xlib_math
///
