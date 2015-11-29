#include <machine.h>
#include <xlib.h>

int machine_inputAndExec(void)
{
	xlib_video_clearScreen();
	xlib_video_writef("%rWelcome to Machine! Press any key to start typing your source.\n%n    - Once you press enter, you will not be able to edit the line you just finished.\n    - The limit for sources is 1000 lines.\n    - When you are done, type \"EOF\" to end your source and execute.\nCommands:\n    - push <num> -> Push a number onto the stack.\n    - pop -> Pop a number off the stack.\n    - add -> Pop the first two numbers off the stack, add them, and push their sum.\n    - ifeq <address> -> If the top of the stack is 0, continue, else, jump to <address>\n    - jump <address> -> Jump to <address>.\n    - print -> Print the value at the top of the stack.\n    - dup -> Push a copy of the first number on the stack back onto the stack.\n    - printc -> Print the value at the top of the stack AS A CHARACTER.");
	xlib_io_getChar();
	
	xlib_video_clearScreen();
	
	char* lines[1000] = {0};
	int i;
	for(i = 0; i < 1000; i++) {
		xlib_video_writeString(xlib_misc_itoa(i, 10));
		xlib_video_writeString(": ");
		char* input = xlib_io_getLine();
		//xlib_video_writeLine(input);
		if(xlib_io_strstart(input, "EOF")) {
			break;
		}
		char* s = malloc(sizeof(char) * 400);
		xlib_io_strcpy(s, input);
		lines[i] = s;
	}
	
	/*xlib_video_writeString("Printing source to test:");
	for(i = 0; i < 10; i++) {
		xlib_video_writeLine(lines[i]);
	}*/
	
	char stack[100] = {0};
	int si = 0;
	for(i = 0; i < 1000; ) {
		if(xlib_io_strstart(lines[i], "EOF")) {
			break;
		}
		//xlib_video_writeLine("Iterate");
		if(xlib_io_strstart(lines[i], "push ")) {
			char num = xlib_io_atoi(lines[i] + 5);
			si++;
			stack[si] = num;
		} else if(xlib_io_strstart(lines[i], "pop")) {
			stack[si] = 0;
			si--;
		} else if(xlib_io_strstart(lines[i], "add")) {
			char num1 = stack[si];
			si--;
			char num2 = stack[si];
			stack[si] = num1 + num2;
		} else if(xlib_io_strstart(lines[i], "ifeq ")) {
			if(stack[si] != 0) {
				i = xlib_io_atoi(lines[i] + 5);
				continue;
			}
		} else if(xlib_io_strstart(lines[i], "jump ")) {
			i = xlib_io_atoi(lines[i] + 5);
			continue;
		} else if(xlib_io_strstart(lines[i], "print")) {
			xlib_video_writeString(xlib_misc_itoa(stack[si], 10));
		} else if(xlib_io_strstart(lines[i], "printc")) {
			xlib_video_writeChar(stack[si]);
		}
		
		i++;
	}
	
	xlib_video_newLine();
}