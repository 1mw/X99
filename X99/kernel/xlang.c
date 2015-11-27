///
/// xlang.c
/// X99 interpreter implementation.
///
/*
#include <xlang/xlang.h>
#include <xlib.h>

int xlang_executeScript(char* src)
{
	xlang_token_t* tokens = malloc(sizeof(xlang_token_t) * 1000);
	long tokenI = 0;
	
	// Parse into tokens
	// Index in src
	long srcI = 0;
	
	{
		char* x;
		for(x = src; *x != 0; ) {
			// Determine if the character is an operator
			bool isOperator = xlang_isOperator(x);
			if(isOperator) {
				if(tokenI < 1) {
					xlib_video_writef("\n%rError: Script begins with an operator.\n");
					return 1;
				}
				// TODO: Implement operators
			} else {
				bool isType = xlang_isType(x);
				if(isType) {
					xlang_type_t type = xlang_getType(x);
					
				} else {
					
				}
			}
		}
	}
}

int xlang_test(char* src)
{
	switch(xlang_getType(src)) {
		case BOOL:
			xlib_video_writeLine("bool");
			break;
		
		case INT:
			xlib_video_writeLine("int");
			break;
	}
}

bool xlang_isOperator(char* characterInSource)
{
	char* l = xlang_operators;
	while(*l != 0) {
		if(*characterInSource == *l) {
			return true;
		}
		l++;
	}
	
	return false;
}

bool xlang_isType(char* characterInSource)
{
	char* value = characterInSource;
	value[xlang_getNextSeparator(characterInSource)] = '\0';
	
	if(xlib_io_strcmp(value, "bool")) {
		return true;
	} else if(xlib_io_strcmp(value, "int")) {
		return true;
	}
}

xlang_type_t xlang_getType(char* characterInSource)
{
	if(!xlang_isType(characterInSource)) {
		xlib_video_writeLinef("\n%rError: xlang_isType was not called before xlang_getType");
	}
	
	char* value = characterInSource;
	value[xlang_getNextSeparator(characterInSource)] = '\0';
	
	if(xlib_io_strcmp(value, "bool") == 0) {
		return BOOL;
	} else if(xlib_io_strcmp(value, "int") == 0) {
		return INT;
	}
}

int xlang_getNextSeparator(char* characterInSource)
{
	char* v = xlang_separators;
	char* x = characterInSource;
	
	for(;;) {
		bool found = false;
		while(*v != 0) {
			if(*x == *v) {
				found = true;
				break;
			}
			
			v++;
		}
		
		if(found == true) {
			return (unsigned long) x - (unsigned long) characterInSource;
		}
		x++;
		v = xlang_separators;
	}
}





*/
