///
/// brain.c
/// Implementation of a brainfuck interpreter.
///

#include <brain.h>
#include <types.h>
#include <xlib.h>

int brain_exec(char* src)
{
	unsigned char tape[30] = {0};
	unsigned char* ptr = tape;
	char current_char;
	size_t i;
	size_t loop;
	
	for(i = 0; src[i] != '\0'; i++) {
		current_char = src[i];
	        if (current_char == '>') {
	        	++ptr;
	        } else if (current_char == '<') {
	        	--ptr;
	        } else if (current_char == '+') {
			++*ptr;
	        } else if (current_char == '-') {
			--*ptr;
	        } else if (current_char == '.' ) {
			xlib_video_writeChar(*ptr);
	        } else if (current_char == ',') {
			*ptr = xlib_io_getChar();
	        } else if (current_char == '[') {
			continue;
	        } else if (current_char == ']' && *ptr) {
			loop = 1;
			while (loop > 0) {
				current_char = src[--i];
				if (current_char == '[') {
					loop--;
				} else if (current_char == ']') {
					loop++;
	                	}
	        	}
	        }
	}
	
	return 1;
}