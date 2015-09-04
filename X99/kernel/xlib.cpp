// xlib.cpp
//
// This is the "standard library" to be used by the kernel and programs.
//
// Copyright (c) 2015, Mark Aldrich, All rights reserved.

#include "xlib.h"

// X99 Library
namespace xlib
{
	namespace video
	{
		int column = 0;
		int row = 0;
		void writeString(const char* string)
		{
			while(*string != 0)
			{
				char* v = (char*) (VIDEO_MEMORY + (((row * 80) + column) * 2));
				*v = *string;
				column++;
				
				if(column >= MAX_COLUMN)
				{
					column = 0;
					row++;
				}
				
				if(row >= MAX_ROW)
				{
					column = 0;
					row = 0;
				}
				
				string++;
			}
		}
		
		void newLine()
		{
			column = 0;
			row++;
			
			if(row >= MAX_ROW)
			{
				row = 0;
			}
		}
	}
	
	namespace misc
	{
		char* itoa(int val, int base)
		{
			
			if(val == 0)
			{
				return "0";
			}
			
			static char buf[32] = {0};
			
			int i = 30;
			
			for(; val && i ; --i, val /= base)
			
			buf[i] = "0123456789abcdef"[val % base];
			
			return &buf[i+1];
			
		}
	}
	
	namespace keyboard
	{
		
	}
	
	namespace io
	{
		
	}
}
