// xlib.h
//
// This is the xlib header file.
//
// Copyright (c) 2015, Mark Aldrich, All rights reserved.

#ifndef ___xlib_
#define ___xlib_

#include "types.h"

namespace xlib
{
	namespace video
	{
		const int VIDEO_MEMORY = 0xb8000;
		const int MAX_COLUMN = 80;
		const int MAX_ROW = 25;
		void writeString(const char* string);
		void newLine();
	}
	
	namespace misc
	{
		char* itoa(int val, int base);
	}
	
	namespace keyboard
	{
		char getChar();
	}
	
	namespace io
	{
		__attribute__((always_inline)) inline void outb(uint16 port, uint8 val)
		{
			__asm__ volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
		}
		
		__attribute__((always_inline)) inline uint8 inb(uint16 port)
		{
			uint8 ret;
			__asm__ volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
			return ret;
		}
	}
}

#endif