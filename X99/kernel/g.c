#include <g.h>
#include <types.h>
#include <xlib.h>

typedef struct {
	char* name;
	uint8_t pointer;
} g_registrytie_t;

char stack[100];
int si = 0;
char registers[100];
g_registrytie_t* ties[100];
int ti = 0;

int g_getNextSeparator(const char* string)
{
	char* x = string;
	for(; *x != ' ' && *x != ':'; x++);
	return x - string;
}

int g_getNextNonSeparator(const char* string)
{
	char* x = string;
	for(; *x == ' ' || *x == ':'; x++);
	return x - string;
}

int g_getRegistryTie(const char* name)
{
	int y;
	for(y = 0; y < ti; y++) {
		if(xlib_io_strcmp(name, ties[y]->name) == 0) {
			return y;
		}
	}
	return -1;
}

int g_inputAndExec()
{
	xlib_video_clearScreen();
	xlib_video_writef("%rWelcome to g! Press any key to start typing your source.");
	xlib_io_getChar();
	
	xlib_video_clearScreen();
	
	char* lines[1000] = {0};
	int i;
	for(i = 0; i < 1000; i++) {
		xlib_video_writeString(xlib_misc_itoa(i, 10));
		xlib_video_writeString(": ");
		char* input = xlib_io_getLine();
		
		if(xlib_io_strstart(input, "EOF")) {
			break;
		}
		
		char* s = malloc(sizeof(char) * 20);
		memset(s, 0, 20);
		xlib_io_strcpy(s, input);
		lines[i] = s;
	}
	
	for(i = 0; i < 1000; ) {
		if(xlib_io_strstart(lines[i], ";")) {
			i++;
			continue;
		}
		if(xlib_io_strstart(lines[i], "@init ")) {
			g_registrytie_t* tie = malloc(sizeof(g_registrytie_t));
			tie->name = malloc(sizeof(char) * 10);
			xlib_io_strcpy(tie->name, lines[i] + 6);
			xlib_video_writeString("@init:: name -> ");
			xlib_video_writeString(lines[i] + 6);
			xlib_video_newLine();
			ties[ti++] = tie;
		}
		if(xlib_io_strstart(lines[i], "@storel ")) { // 8
			char* var = malloc(sizeof(char) * 10);
			memset(var, 0, 10);
			xlib_io_strcpy(var, lines[i] + 8);
			int sep = g_getNextSeparator(var);
			var[sep] = '\0';
			char* literal = malloc(sizeof(char) * 4);
			xlib_io_strcpy(literal, lines[i] + 8 + sep);
			int l = xlib_io_atoi(literal);
			
			int h = g_getRegistryTie(var);
			if(h == -1) {
				xlib_video_writef("%rCould not find variable: ");
				xlib_video_writeString(var);
				xlib_sys_panic("store", __FILE__, __FUNCTION__, __LINE__);
				return 1;
			}
			
			registers[h] = l;
		}
		if(xlib_io_strstart(lines[i], "@printv ")) { // 8
			char* var = malloc(sizeof(char) * 10);
			xlib_io_strcpy(var, lines[i] + 8);
			int h = g_getRegistryTie(var);
			if(h == -1) {
				xlib_video_writef("%rCould not find variable: ");
				xlib_video_writeString(var);
				xlib_sys_panic("printv", __FILE__, __FUNCTION__, __LINE__);
				return 1;
			}
			xlib_video_writeString(xlib_misc_itoa(registers[h], 10));
		}
		
		i++;
	}
	
	xlib_video_newLine();
	xlib_video_writeLine("Printing registry:");
	int j;
	for(j = 0; j < 10; j++) {
		xlib_video_writeString(xlib_misc_itoa(j, 10));
		xlib_video_writeString(": ");
		xlib_video_writeString(xlib_misc_itoa(registers[j], 10));
		xlib_video_newLine();
	}
}