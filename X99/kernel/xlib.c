///
/// xlib.c
/// xlib implementation. xlib is the X99 standard library.
///

#include <xlib.h>
#include <types.h>
#include <memory/memory.h>

///
/// xlib_video
///

int xlib_video_column = 0;
int xlib_video_row = 0;

void xlib_video_writeString(const char* string)
{
	int color = 0x07;
        while(*string != 0) {
		char* v = (char*) (xlib_video_VIDEO_MEMORY + (((xlib_video_row * 80) + xlib_video_column) * 2));
	        if(*string != '\n') {
			*v++ = *string;
			*v++ = color;
			xlib_video_column++;

			if(xlib_video_column >= xlib_video_MAX_COLUMN) {
				xlib_video_newLine();
			}
	        } else {
			xlib_video_newLine();
	        }

		string++;
	}
}

void xlib_video_writef(const char* formattedString)
{
	int color = 0x07;
	while(*formattedString != 0) {
		char* v = (char*) (xlib_video_VIDEO_MEMORY + (((xlib_video_row * 80) + xlib_video_column) * 2));
		if(*formattedString != '%') {
			if(*formattedString != '\n') {
				*v++ = *formattedString;
				*v = color;

				xlib_video_column++;

				if(xlib_video_column >= xlib_video_MAX_COLUMN)
					xlib_video_newLine();
			} else {
				xlib_video_newLine();
			}

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

void xlib_video_newLine(void)
{
	xlib_video_column = 0;
	xlib_video_row++;
	
	if(xlib_video_row >= xlib_video_MAX_ROW) {
		xlib_video_clearScreen();
	}
}

void xlib_video_clearScreen(void)
{
	int x, y;
	for(x = 0; x < xlib_video_MAX_COLUMN; x++) {
		for(y = 0; y < xlib_video_MAX_ROW; y++) {
			char* mem = (char*) 0xb8000 + (((y * xlib_video_MAX_COLUMN) + x) * 2);
			*mem++ = 0;
			*mem++ = 0;
		}
	}
	
	xlib_video_row = 0;
	xlib_video_column = 0;
}

void xlib_video_writeChar(const char character)
{
	char string[2];
	string[0] = character;
	string[1] = '\0';
	
	xlib_video_writeString(string);
}

void xlib_video_writeLine(const char* line)
{
	xlib_video_writeString(line);
	xlib_video_newLine();
}

void xlib_video_writeLinef(const char* formattedLine)
{
	xlib_video_writef(formattedLine);
	xlib_video_newLine();
}

///
/// end xlib_video
///

///
/// xlib_io
///
bool shiftKeyIsDown = false;

char xlib_io_getScancode(void)
{
	return xlib_io_inb(0x60);
}

unsigned int xlib_io_getAndAnalyzeScancode(void)
{
        unsigned int scancode;
        while(1) {
                // Wait for the keyboard to tell us that there is a key pressed
                while(!(xlib_io_inb(0x64) & 1));
		
                scancode = xlib_io_getScancode();
		
                if (((scancode & 0x7f) == 0x2a) || ((scancode & 0x7f) == 0x36)) {
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

char xlib_io_getChar(void)
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
char* xlib_io_getLine(void)
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

char* xlib_io_strcpy(char* dst, const char* src)
{
	char *ptr;
	ptr = dst;
	while(*dst++ = *src++);
	
	return(ptr);
}

char* xlib_io_strcat(char* dst, const char* src)
{
	char *rdest = dst;

	while (*dst) {
		dst++;
	}
	
	while (*dst++ = *src++);
	
	return rdest;
}

size_t xlib_io_strlen(const char* str)
{
	const char* s;
	
	for(s = str; *s; s++);
	
	return (s - str);
}

int xlib_io_strcmp(const char* s1, const char* s2)
{
	const unsigned char *p1 = (const unsigned char *)s1;
	const unsigned char *p2 = (const unsigned char *)s2;

	while (*p1 != '\0') {
		if (*p2 == '\0') return  1;
		if (*p2 > *p1)   return -1;
		if (*p1 > *p2)   return  1;

		p1++;
		p2++;
	}

	if (*p2 != '\0') return -1;

	return 0;
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
/// xlib_memory (some functions have no prefix because of how common they are)
///

unsigned int xlib_memory_mmapStarts[100] = {0};
unsigned int xlib_memory_mmapEnds[100] = {0};
unsigned int xlib_memory_mmapType[100] = {0};
unsigned int xlib_memory_mmapLength[100] = {0};
unsigned int xlib_memory_numberOfEntries;
unsigned int xlib_memory_mmapLastIndex;
unsigned int xlib_memory_mmapLastAddress;

bool xlib_memory_didInit = false;

void xlib_memory_init(multiboot_info_t* mbt, unsigned int magic)
{
        xlib_video_writef(">> Initiating %mxlib_memory%n...\n");
        xlib_video_writeString("    Making sure memory was not already initiated...");
        // Make sure this is the first time
        if(xlib_memory_didInit) {
        	xlib_sys_panic("xlib_memory_init :: Trying to initiate memory when memory has already been initiated.");
        }
        xlib_video_writef(OK);

	xlib_video_writeString("    Checking to see if GRUB's mmap_* fields are valid...");
	if(!multiboot_checkFlag(mbt->flags, 1)) {
		xlib_sys_panic("xlib_memory_init :: GRUB's mmap_* fields are not valid. Cannot initialize memory.");
	}
	xlib_video_writef(OK);

        xlib_video_writeString("    Verifying magic number...");
        // Verify magic number
        /*
        if(magic != 0x1BADB002) {
        xlib_sys_panic("xlib_memory_init :: Multiboot magic number mismatch.");
        }*/
        xlib_video_writef(OK);
        xlib_video_writeString("        Magic number is: 0x");
        xlib_video_writeString(xlib_misc_itoa(magic, 16));
        xlib_video_newLine();

        // Iterate through entries
	xlib_video_writeString("    Iterating through entries and recording available positions...\n");
	multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) mbt->mmap_addr;
	xlib_video_writeString("        mmap_addr -> 0x");
	xlib_video_writeString(xlib_misc_itoa((unsigned int) mbt->mmap_addr, 16));
	xlib_video_newLine();
	xlib_video_writeString("        mmap_length -> 0x");
	xlib_video_writeString(xlib_misc_itoa((unsigned int) mbt->mmap_length, 16));
	xlib_video_newLine();
	
	int i = 0;
	while((unsigned long) mmap < mbt->mmap_addr + mbt->mmap_length) {
		xlib_memory_mmapStarts[i] = mmap->addr;
		xlib_memory_mmapEnds[i] = mmap->addr + mmap->len;
		xlib_memory_mmapLength[i] = mmap->len;
		xlib_memory_mmapType[i] = mmap->type;
		
		xlib_memory_numberOfEntries++;
		
		mmap = (multiboot_memory_map_t*) ((unsigned int) mmap + mmap->size + sizeof(unsigned int));
		i++;
	}
	
        xlib_video_writeString("    Preventing more memory initiations...");
        xlib_memory_didInit = true;
        xlib_video_writef(OK);
}

void* malloc(int size)
{
        if(xlib_memory_didInit) {
                if(xlib_memory_mmapLastAddress == 0) {
			xlib_memory_mmapLastIndex = 0;
			
			while(1) {
				xlib_memory_mmapLastAddress = xlib_memory_mmapStarts[xlib_memory_mmapLastIndex];
				
				if(xlib_memory_mmapType[xlib_memory_mmapLastIndex] != 1 || xlib_memory_mmapLength[xlib_memory_mmapLastIndex] == 0 || xlib_memory_mmapStarts[xlib_memory_mmapLastIndex] == 0) {
					xlib_memory_mmapLastIndex++;
					continue;
				}
				
				break;
			}
		}
		
		start:
		if(xlib_memory_mmapEnds - xlib_memory_mmapLastAddress > size) {
			xlib_memory_mmapLastAddress += size;
			return (void*) xlib_memory_mmapLastAddress;
		} else {
			inc:
			xlib_memory_mmapLastIndex++;
			
			if(xlib_memory_mmapLastIndex > xlib_memory_numberOfEntries) {
				xlib_sys_panic("malloc :: Out of memory!");
			}
			
			if(xlib_memory_mmapType[xlib_memory_mmapLastIndex] != 1 || xlib_memory_mmapLength[xlib_memory_mmapLastIndex] == 0 || xlib_memory_mmapStarts[xlib_memory_mmapLastIndex] == 0) {
				goto inc;
			}
			
			goto start;
		}
        } else {
                xlib_sys_panic("malloc :: Memory not initiated.");
                return NULL;
        }
}

void* calloc(int size)
{
	void* ptr = malloc(size);
	memset(ptr, 0, size);
	
	return ptr;
}

void* memset(void* dst, int c, size_t n)
{
	if(n) {
		char* d = dst;
		
		do {
			*d++ = c;
		} while(--n);
	}
	
	return dst;
}

void free(void* ptr)
{
	
}

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
