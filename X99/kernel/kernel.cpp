// kernel.cpp
//
// This is the main kernel file for the X99 operating system.
//
// Copyright (c) 2015, Mark Aldrich, All rights reserved.


#include "kernel.h"
#include "xlib.h"

extern "C"
void kernel_main()
{
	xlib::video::writeString("Welcome to the X99 operating system.");
}